#include "Graphics.hpp" 

#include "debugAssert.hpp"
#include "filesystem.hpp"

#include <cstring>
#include <cstdint>

namespace Graphics {
/********************************************************
 * glCheck
********************************************************/
#define GL_DEBUG

#ifdef GL_DEBUG
	#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#else
	#define glCheck(call) (call)
#endif

void glCheckError(const std::string& file, unsigned int line){
    // Get the last error
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR)
    {
        std::string error = "unknown error";
        std::string description  = "no description";

        // Decode the error code
        switch (errorCode)
        {
            case GL_INVALID_ENUM :
            {
                error = "GL_INVALID_ENUM";
                description = "an unacceptable value has been specified for an enumerated argument";
                break;
            }

            case GL_INVALID_VALUE :
            {
                error = "GL_INVALID_VALUE";
                description = "a numeric argument is out of range";
                break;
            }

            case GL_INVALID_OPERATION :
            {
                error = "GL_INVALID_OPERATION";
                description = "the specified operation is not allowed in the current state";
                break;
            }

            /*case GL_STACK_OVERFLOW :
            {
                error = "GL_STACK_OVERFLOW";
                description = "this command would cause a stack overflow";
                break;
            }

            case GL_STACK_UNDERFLOW :
            {
                error = "GL_STACK_UNDERFLOW";
                description = "this command would cause a stack underflow";
                break;
            }*/

            case GL_OUT_OF_MEMORY :
            {
                error = "GL_OUT_OF_MEMORY";
                description = "there is not enough memory left to execute the command";
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION :
            {
                error = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
                description = "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
                break;
            }
        }

        //std::cout<<"Warning OpenGL in \""<<file<<"\" (l"<<line<<") : "<<error<<" ; "<<description<<std::endl;

        debug::assert("glCheck", false, "An internal OpenGL call failed in ", file, " ( ", line, " ) : ", error, ", ", description);
    }
}
	
/********************************************************
 * Graphics main
********************************************************/
	void createGraphics(){
	  glCheck(glEnable(GL_DEPTH_TEST));

	  // Enable blending
	  glEnable(GL_BLEND);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void destroyGraphics(){
		
	}
	
/********************************************************
 * Texture
********************************************************/
// dds file format
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

  union DDS_header {
    struct {
      //uint32_t dwMagic;
      uint32_t dwSize;
      uint32_t dwFlags;
      uint32_t dwHeight;
      uint32_t dwWidth;
      uint32_t dwPitchOrLinearSize;
      uint32_t dwDepth;
      uint32_t dwMipMapCount;
      uint32_t dwReserved1[ 11 ];
      
      //  DDPIXELFORMAT
      struct {
	uint32_t dwSize;
        uint32_t dwFlags;
        uint32_t dwFourCC;
        uint32_t dwRGBBitCount;
        uint32_t dwRBitMask;
        uint32_t dwGBitMask;
        uint32_t dwBBitMask;
        uint32_t dwAlphaBitMask;
      } sPixelFormat;
      
      //  DDCAPS2
      struct {
	uint32_t dwCaps1;
        uint32_t dwCaps2;
        uint32_t dwDDSX;
        uint32_t dwReserved;
      } sCaps;
      
      uint32_t dwReserved2;
    };
    char data[ 124 ];
  };

  
	Texture::Texture() { glGenTextures(1, &mId); }

  Texture::~Texture() { glDeleteTextures(1, &mId); }

  void Texture::load(std::string filename) {
    mName = filename;

    DDS_header header;
    
    std::string filename2 = filesystem::getBaseDirectory() +
      filesystem::getGameDirectory() +
      filesystem::getPathSeparator() +
      filename;

    //open file
    std::fstream file(filename2, std::fstream::in | std::fstream::binary);
    debug::assert("Texture", file.is_open(), "error with dds file : \"", filename2, "\"");

    /* vérifie le type du fichier */
    char filecode[4];
    file.read(filecode, 4);
    if (strncmp(filecode, "DDS ", 4) != 0) {
      file.close();
      debug::assert("Texture", false, "error in dds file");
    }

    /* récupère la description de la surface */
    file.read(header.data, sizeof(DDS_header));

    unsigned int height = header.dwHeight;
    unsigned int width =  header.dwWidth;
    unsigned int linearSize = header.dwPitchOrLinearSize;
    unsigned int mipMapCount = header.dwMipMapCount;
    unsigned int fourCC = header.sPixelFormat.dwFourCC;

    char *buffer;
    unsigned int bufsize;
    /* quelle va être la taille des données incluant les MIP maps ? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (char *)malloc(bufsize * sizeof(unsigned char));
    file.read(buffer, bufsize);
    /* fermer le pointeur de fichier */
    file.close();

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC) {
    case FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
    case FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    default:
      free(buffer);
      debug::assert("Texture", false, "unsupported dds format");
    }

    // Crée une texture OpenGL

    // "Lie" la nouvelle texture : tous les futurs appels aux fonctions de texture
    // vont modifier cette texture
    glCheck(glBindTexture(GL_TEXTURE_2D, mId));

    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			    GL_LINEAR_MIPMAP_LINEAR));

    unsigned int blockSize =
      (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* charge les MIP maps */
    for (unsigned int level = 0; level < mipMapCount && (width || height);
	 ++level) {
      unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
      glCheck(glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				     0, size, buffer + offset));

      offset += size;
      width /= 2;
      height /= 2;
    }
    free(buffer);

    debug::assert("Texture", mId != 0, "error with a texture");
  }

  unsigned int Texture::getId() { return mId; }

  void Texture::set() {
    glCheck(glActiveTexture(GL_TEXTURE0));
    glCheck(glBindTexture(GL_TEXTURE_2D, mId));
  }

  std::string Texture::getName(){
    return mName;
  }
  
/********************************************************
 * Shader
********************************************************/

void Shader::load(const char *vertCode, const char *fragCode) {
    GLuint v, f;

    glCheck(v = glCreateShader(GL_VERTEX_SHADER));
    glCheck(f = glCreateShader(GL_FRAGMENT_SHADER));

    glCheck(glShaderSource(v, 1, &vertCode, NULL));
    glCheck(glShaderSource(f, 1, &fragCode, NULL));

    glCheck(glCompileShader(v));
    glCheck(glCompileShader(f));

    printShaderInfoLog(v);
    printShaderInfoLog(f);

    glCheck(shaderProgram = glCreateProgram());
    glCheck(glAttachShader(shaderProgram, v));
    glCheck(glAttachShader(shaderProgram, f));

    glCheck(glBindFragDataLocation(shaderProgram, 0, "outputF"));
    glCheck(glLinkProgram(shaderProgram));
    printProgramInfoLog(shaderProgram);

    glCheck(glDeleteShader(v));
    glCheck(glDeleteShader(f));
  }

  Shader::Location Shader::addMatrixInput(std::string name) {
    Shader::Location loc;
    glCheck(loc = glGetUniformLocation(shaderProgram, name.c_str()));
    return loc;
  }

  void Shader::setMatrixInput(Location loc, math::Matrix4f mat) {
    glCheck(glUseProgram(shaderProgram));
    glCheck(glUniformMatrix4fv(loc, 1, false, &mat.m[0][0]));
  }

  Shader::Location Shader::addTextureInput(std::string name) {
    Shader::Location loc;
    glCheck(loc = glGetUniformLocation(shaderProgram, name.c_str()));
    debug::assert("Shader", loc > 0, "no texture input");
    return loc;
  }

  void Shader::addBufferInput(std::string name, unsigned int i) {
    glCheck(glBindAttribLocation(shaderProgram, i, name.c_str()));
  }

  void Shader::set() { glCheck(glUseProgram(shaderProgram)); }

  void Shader::unload() { glCheck(glDeleteProgram(shaderProgram)); }

  void Shader::printShaderInfoLog(GLuint obj) {
    int infologLength = 0;
    int charsWritten = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

    if (infologLength > 1) {
      infoLog = (char *)malloc(infologLength);
      glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
      printf("%s\n", infoLog);
      free(infoLog);
    }
  }

  void Shader::printProgramInfoLog(
				   GLuint obj) { /*
						   GLint param;
						   glCheck(glGetProgramiv(obj, GL_LINK_STATUS, &param));
						   debug::log("Shader", "\tGL_LINK_STATUS ",
						   (param==GL_TRUE)?"true":"false");

						   glCheck(glGetProgramiv(obj, GL_ATTACHED_SHADERS,
						   &param));
						   debug::log("Shader", "\tGL_ATTACHED_SHADERS ", param);

						   //attribute
						   {
						   GLint nbActiveAttribute, maxLengthName,
						   lengthName, size;
						   GLenum type;

						   debug::log("Shader", "\tactive attribute");

						   glCheck(glGetProgramiv(obj,
						   GL_ACTIVE_ATTRIBUTES, &nbActiveAttribute));
						   glCheck(glGetProgramiv(obj,
						   GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLengthName));

						   char name[maxLengthName];
						   char* typeName;

						   for(unsigned int index(0);
						   index<nbActiveAttribute; ++index){
						   glCheck(glGetActiveAttrib(obj, index,
						   maxLengthName, &lengthName, &size, &type, name));

						   typeName = getTypeName(type);

						   debug::log("Shader", "\t\t", typeName,"
						   ", name, "[", size, "]");
						   }
						   }
						   //unifrom
						   {
						   GLint nbUniform, maxLengthName, lengthName,
						   size;
						   GLenum type;
						   char* typeName;

						   debug::log("Shader", "\tactive uniform");

						   glCheck(glGetProgramiv(obj, GL_ACTIVE_UNIFORMS,
						   &nbUniform));
						   glCheck(glGetProgramiv(obj,
						   GL_ACTIVE_UNIFORM_MAX_LENGTH , &maxLengthName));

						   char name[maxLengthName];

						   for(unsigned int index(0); index<nbUniform;
                     ++index){
                                         glGetActiveUniform(obj, index,
                     maxLengthName, &lengthName, &size, &type, name);

                                         typeName = getTypeName(type);

                                         debug::log("Shader", "\t\t", typeName,"
                     ", name, "[", size, "]");
                                 }
                         }
                         */
  // log
  int infologLength = 0;
  int charsWritten = 0;
  char *infoLog;

  glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

  if (infologLength > 1) {
    infoLog = (char *)malloc(infologLength);
    glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
    printf("shader info : \"%s\"\n", infoLog);
    free(infoLog);
  }
}

const char *Shader::getTypeName(GLenum type) {
  std::string result;
  switch (type) {
  case GL_FLOAT:
    result = "float";
    break;
  case GL_FLOAT_VEC2:
    result = "vec2f";
    break;
  case GL_FLOAT_VEC3:
    result = "vec3f";
    break;
  case GL_FLOAT_VEC4:
    result = "vec4f";
    break;
  case GL_FLOAT_MAT4:
    result = "mat4f";
    break;
  case GL_SAMPLER_2D:
    result = "sampler2D";
    break;
  default:
    result = "unkown";
    break;
  }
  return result.c_str();
}
  
/********************************************************
 * SubMesh
********************************************************/
  void SubMesh::beginLoad(){
		glCheck(glGenVertexArrays(1, &mId));
		glCheck(glBindVertexArray(mId));
	}
	
	void SubMesh::addBuffer(Graphics::Shader::Location loc, const float* data, unsigned int dataSize, unsigned int size){
		GLuint buffer;
		glCheck(glGenBuffers(1, &buffer));
		glCheck(glBindBuffer(GL_ARRAY_BUFFER, buffer));
		glCheck(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));
		
		glCheck(glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, 0, 0));
		glCheck(glEnableVertexAttribArray(loc));
	}
	
	void SubMesh::endLoad(Primitives primitives, unsigned int count){
		mWithIndex = false;
		mPrimitives = primitives;
		mCount = count;
		debug::log("SubMesh", "\tend");
	}
	
	void SubMesh::endLoadWithIndex(Primitives primitives, unsigned int count, const unsigned int* data){
		mWithIndex = true;
		mPrimitives = primitives;
		mCount = count;
		
		GLuint buffer;
		
		glCheck(glGenBuffers(1, &buffer));
		glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffer));
		glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					sizeof(unsigned int)*count,
					data,
					GL_STATIC_DRAW));
	}
	
	void SubMesh::draw(){
		glCheck(glBindVertexArray(mId));
		if(mWithIndex){
			glCheck(glDrawElements(/*mPrimitives*/GL_TRIANGLES,
						mCount,
						GL_UNSIGNED_INT,
						(void *)0));
		}else{
			glCheck(glDrawArrays(mPrimitives, 0, mCount));
		}
		
	}

	void SubMesh::unload(){
		glCheck(glDeleteVertexArrays(1, &mId));
	}

}
