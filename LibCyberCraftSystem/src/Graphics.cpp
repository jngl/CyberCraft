#include "System/Graphics.hpp"

#include <Core/Debug.h>
#include <algorithm>

#include "System/DdsFile.h"

namespace cs {

/********************************************************
 * glCheck
********************************************************/
#define GL_DEBUG

#ifdef GL_DEBUG
#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))  // NOLINT
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
        cc::check("glCheck", errorCode == GL_NO_ERROR, "An internal OpenGL call failed in ", file, " ( ", line, " ) : ", getGlErrorMessage(errorCode) );
        //std::cout<<"An internal OpenGL call failed in "<<file<<" ( "<<line<<" ) : "<<getGlErrorMessage(errorCode);
    }

    /********************************************************
     * TextureGL
    ********************************************************/
    unsigned int TextureGlLoad(const TextureData& data){
        unsigned int id;

        glGenTextures(1, &id);

        glCheck(glBindTexture(GL_TEXTURE_2D, id));

        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                GL_LINEAR_MIPMAP_LINEAR));

        unsigned int format = 0;
        switch (data.format) {
            case TextureFormat::DXT1:
                format =  GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
                break;
            case TextureFormat::DXT3:
                format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
                break;
            case TextureFormat::DXT5:
                format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
                break;
        }
        cc::check("TextureGL", format != 0, "invalid format");

        int level = 0;
        for(const auto& mipMap : data.mipmaps){
            glCheck(glCompressedTexImage2D(GL_TEXTURE_2D,
                                           level,
                                           format,
                                           static_cast<GLsizei>(mipMap.size.x),
                                            static_cast<GLsizei>(mipMap.size.y),
                                           0,
                                            static_cast<GLsizei>(mipMap.data.size()),
                                            mipMap.data.data()));
            level++;
        }

        cc::check("TextureGL", id != 0, "error with a texture");

        return id;
    }

    unsigned int TextureGlLoad(std::string_view fileName){
        TextureData data = readDdsFile(fileName);
        return TextureGlLoad(data);
    }

    void TextureGlUnload(unsigned int id){
        glDeleteTextures(1, &id);
    }

/********************************************************
 * Graphics Context
********************************************************/
    GraphicsContext::GraphicsContext() {
        glCheck(glEnable(GL_DEPTH_TEST));

        // Enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void GraphicsContext::setCurrentTexture(cc::TextureHandle handle) {
        const Texture& texture = m_textures.at(handle.value());

        glCheck(glActiveTexture(GL_TEXTURE0));
        glCheck(glBindTexture(GL_TEXTURE_2D, texture.glId));

        m_current_texture = handle;
    }

    cc::TextureHandle GraphicsContext::getCurrentTexture() const {
        return m_current_texture;
    }

    cc::TextureHandle GraphicsContext::getHandleFromFile(std::string_view filename) {
        auto it = std::find_if(begin(m_textures), end(m_textures), [filename](const Texture& tex ){
            return tex.fileName == filename;
        });

        if(it != std::end(m_textures)){
            return cc::TextureHandle(static_cast<uint>(std::distance(std::begin(m_textures), it)));
        }

        m_textures.emplace_back();
        m_textures.back().fileName = filename;

        return cc::TextureHandle(static_cast<uint>(m_textures.size()-1));
    }

    void GraphicsContext::loadTexture(cc::TextureHandle texture) {
        Texture& textureData = m_textures.at(texture.value());
        textureData.glId = TextureGlLoad(textureData.fileName);
    }

    void GraphicsContext::unloadTexture(cc::TextureHandle texture) {
        Texture& textureData = m_textures.at(texture.value());
        TextureGlUnload(textureData.glId);
        textureData.glId = 0;
    }

/********************************************************
 * Shader
********************************************************/

    void Shader::load(const char *vertCode, const char *fragCode) {
        GLuint v = 0;
        GLuint f = 0;

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

    Shader::Location Shader::addMatrixInput(const std::string& name) {  // NOLINT
        Shader::Location loc = 0;
        glCheck(loc = static_cast<Shader::Location>(glGetUniformLocation(shaderProgram, name.c_str())));
        return loc;
    }

    void Shader::setMatrixInput(Location loc, cc::Matrix4f mat) {  // NOLINT
        glCheck(glUseProgram(shaderProgram));
        glCheck(glUniformMatrix4fv(static_cast<GLint>(loc), 1, false, &mat.m[0][0]));
    }

//    Shader::Location Shader::addTextureInput(const std::string& name) {  // NOLINT
//        Shader::Location loc = 0;
//        glCheck(loc = glGetUniformLocation(shaderProgram, name.c_str()));
//        cc::check("Shader", loc > 0, "no texture input");
//        return loc;
//    }

    void Shader::addBufferInput(const std::string& name, unsigned int i) {  // NOLINT
        glCheck(glBindAttribLocation(shaderProgram, i, name.c_str()));
    }

    void Shader::set() { glCheck(glUseProgram(shaderProgram)); }  // NOLINT

//    void Shader::unload() { glCheck(glDeleteProgram(shaderProgram)); }  // NOLINT

    void Shader::printShaderInfoLog(GLuint obj) {
        int infologLength = 0;
        int charsWritten = 0;

        glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

        if (infologLength > 1) {
            std::string infoLog;
            infoLog.resize(static_cast<size_t>(infologLength), '?');
            glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog.data());
            std::cout<<infoLog<<"\n";
        }
    }

    void Shader::printProgramInfoLog(
            GLuint obj) {
        // log
        int infoLogLength = 0;
        int charsWritten = 0;

        glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &infoLogLength);

        if (infoLogLength > 1) {
            std::string infoLog;
            infoLog.resize(static_cast<size_t>(infoLogLength), '?');
            glGetProgramInfoLog(obj, infoLogLength, &charsWritten, infoLog.data());
            std::cout<<"shader info : \""<<infoLog<<"\"\n";
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
 * Mesh
********************************************************/
    void Mesh::beginLoad() {
        glCheck(glGenVertexArrays(1, &mId));
        glCheck(glBindVertexArray(mId));
    }

    void
    Mesh::addBuffer(Shader::Location loc, const float *data, unsigned int dataSize, unsigned int size) {  // NOLINT
        GLuint buffer = 0;
        glCheck(glGenBuffers(1, &buffer));
        glCheck(glBindBuffer(GL_ARRAY_BUFFER, buffer));
        glCheck(glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW));

        glCheck(glVertexAttribPointer(loc, static_cast<GLint>(size), GL_FLOAT, GL_FALSE, 0, nullptr));
        glCheck(glEnableVertexAttribArray(loc));
    }

    void Mesh::endLoad(Primitives primitives, unsigned int count) {
        mWithIndex = false;
        mPrimitives = primitives;
        mCount = count;
        cc::log("Mesh", "\tend");
    }

    void Mesh::endLoadWithIndex(Primitives primitives, unsigned int count, const unsigned int *data) {
        mWithIndex = true;
        mPrimitives = primitives;
        mCount = count;

        GLuint buffer = 0;

        glCheck(glGenBuffers(1, &buffer));
        glCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer));
        glCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             sizeof(unsigned int) * count,
                             data,
                             GL_STATIC_DRAW));
    }

    void Mesh::draw() {
        glCheck(glBindVertexArray(mId));
        if (mWithIndex) {
            glCheck(glDrawElements(/*mPrimitives*/GL_TRIANGLES,
                                                  static_cast<GLsizei>(mCount),
                                                  GL_UNSIGNED_INT,
                                                  nullptr));
        } else {
            glCheck(glDrawArrays(mPrimitives, 0, static_cast<GLsizei>(mCount)));
        }

    }

    void Mesh::unload() {
        glCheck(glDeleteVertexArrays(1, &mId));
    }
}
