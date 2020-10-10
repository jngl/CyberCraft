#include "System/Graphics.hpp"

#include <Core/Debug.h>
#include "System/filesystem.hpp"

#include "DdsFile.h"

#include <cstring>
#include <cstdint>

namespace cc::System {

/********************************************************
 * glCheck
********************************************************/
#define GL_DEBUG

#ifdef GL_DEBUG
#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#else
#define glCheck(call) (call)
#endif

    std::string_view getGlErrorMessage(GLenum errorCode){
        switch (errorCode) {
            case GL_INVALID_ENUM :
                return "GL_INVALID_ENUM : an unacceptable value has been specified for an enumerated argument";
            case GL_INVALID_VALUE :
                return "GL_INVALID_VALUE : a numeric argument is out of range";
            case GL_INVALID_OPERATION :
                return "GL_INVALID_OPERATION : the specified operation is not allowed in the current state";
            case GL_OUT_OF_MEMORY :
                return "GL_OUT_OF_MEMORY : there is not enough memory left to execute the command";
            case GL_INVALID_FRAMEBUFFER_OPERATION :
                return "GL_INVALID_FRAMEBUFFER_OPERATION_EXT : the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
            default:
                return "unknown";
        }
    }

    void glCheckError(const std::string &file, unsigned int line) {
        GLenum errorCode = glGetError();
        ccCore::check("glCheck", errorCode == GL_NO_ERROR, "An internal OpenGL call failed in ", file, " ( ", line, " ) : ", getGlErrorMessage(errorCode) );
    }

    /********************************************************
     * Texture
    ********************************************************/
    class Texture {
    public:
        explicit Texture(std::string_view filename);
        ~Texture() { glDeleteTextures(1, &mId); }

        [[nodiscard]] unsigned int getId() const { return mId; }

    private:
        GLuint mId = 0;
    };

    Texture::Texture(std::string_view filename) {
        DdsFile ddsFile(filename);

        glGenTextures(1, &mId);

        unsigned int format = ddsFile.getFormat();

        ccCore::check("Texture", format != 0, "unsupported dds format");

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

        unsigned int width = ddsFile.getWidth();
        unsigned int height = ddsFile.getHeight();

        /* charge les MIP maps */
        for (unsigned int level = 0; level < ddsFile.getMipMapCount() && (width || height);
             ++level) {
            unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
            glCheck(glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                                           0, size, ddsFile.getBuffer() + offset));

            offset += size;
            width /= 2;
            height /= 2;
        }

        ccCore::check("Texture", mId != 0, "error with a texture");
    }

/********************************************************
 * Graphics main
********************************************************/
    GraphicsContext::GraphicsContext() {
        glCheck(glEnable(GL_DEPTH_TEST));

        // Enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    std::shared_ptr<Texture> GraphicsContext::loadTexture(std::string_view filename) {
        std::string filenameStr(filename);

        auto it = m_textures.find(filenameStr);

        std::shared_ptr<Texture> texture;

        if(it == m_textures.end()){
            texture = std::make_shared<Texture>(filename);
            m_textures[filenameStr] = texture;
        }else{
            texture = it->second.lock();
        }

        return texture;
    }

    void GraphicsContext::set(const std::shared_ptr<Texture> &texture) {
        glCheck(glActiveTexture(GL_TEXTURE0));
        glCheck(glBindTexture(GL_TEXTURE_2D, texture->getId()));
        m_current_texture = texture;
    }

/********************************************************
 * Shader
********************************************************/

    void Shader::load(const char *vertCode, const char *fragCode) {
        GLuint v, f;

        glCheck(v = glCreateShader(GL_VERTEX_SHADER));
        glCheck(f = glCreateShader(GL_FRAGMENT_SHADER));

        glCheck(glShaderSource(v, 1, &vertCode, nullptr));
        glCheck(glShaderSource(f, 1, &fragCode, nullptr));

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

    void Shader::setMatrixInput(Location loc, ccCore::Matrix4f mat) {
        glCheck(glUseProgram(shaderProgram));
        glCheck(glUniformMatrix4fv(loc, 1, false, &mat.m[0][0]));
    }

    Shader::Location Shader::addTextureInput(std::string name) {
        Shader::Location loc;
        glCheck(loc = glGetUniformLocation(shaderProgram, name.c_str()));
        ccCore::check("Shader", loc > 0, "no texture input");
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
            infoLog = (char *) malloc(infologLength);
            glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
            printf("%s\n", infoLog);
            free(infoLog);
        }
    }

    void Shader::printProgramInfoLog(
            GLuint obj) {
        // log
        int infoLogLength = 0;
        int charsWritten = 0;
        char *infoLog;

        glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            infoLog = (char *) malloc(infoLogLength);
            glGetProgramInfoLog(obj, infoLogLength, &charsWritten, infoLog);
            printf("shader info : \"%s\"\n", infoLog);
            free(infoLog);
        }
    }

    std::string_view Shader::getTypeName(GLenum type) {
        std::string_view result;
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
        return result;
    }

/********************************************************
 * SubMesh
********************************************************/
    void SubMesh::beginLoad() {
        glCheck(glGenVertexArrays(1, &mId));
        glCheck(glBindVertexArray(mId));
    }

    void
    SubMesh::addBuffer(Shader::Location loc, const float *data, unsigned int dataSize, unsigned int size) {
        GLuint buffer;
        glCheck(glGenBuffers(1, &buffer));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        glCheck(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));

        glCheck(glVertexAttribPointer(loc, size, GL_FLOAT, GL_FALSE, 0, 0));
        glCheck(glEnableVertexAttribArray(loc));
    }

    void SubMesh::endLoad(Primitives primitives, unsigned int count) {
        mWithIndex = false;
        mPrimitives = primitives;
        mCount = count;
        ccCore::log("SubMesh", "\tend");
    }

    void SubMesh::endLoadWithIndex(Primitives primitives, unsigned int count, const unsigned int *data) {
        mWithIndex = true;
        mPrimitives = primitives;
        mCount = count;

        GLuint buffer;

        glCheck(glGenBuffers(1, &buffer));
        glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
        glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             sizeof(unsigned int) * count,
                             data,
                             GL_STATIC_DRAW));
    }

    void SubMesh::draw() {
        glCheck(glBindVertexArray(mId));
        if (mWithIndex) {
            glCheck(glDrawElements(/*mPrimitives*/GL_TRIANGLES,
                                                  mCount,
                                                  GL_UNSIGNED_INT,
                                                  (void *) 0));
        } else {
            glCheck(glDrawArrays(mPrimitives, 0, mCount));
        }

    }

    void SubMesh::unload() {
        glCheck(glDeleteVertexArrays(1, &mId));
    }
}
