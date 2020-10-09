#pragma once

#include <Core/Math.h>
#include "System/Common.h"

#include "glad/glad.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace cc::System {
    class Texture;

    class GraphicsContext
    {
    public:
        GraphicsContext();

        std::shared_ptr<Texture> loadTexture(std::string_view filename);

        void set(const std::shared_ptr<Texture> &texture);

    private:
        std::unordered_map<std::string, std::weak_ptr<Texture>> m_textures;
        std::weak_ptr<Texture> m_current_texture;
    };


    class Shader {
    public:
        typedef unsigned int Location;

        void load(const char *vertCode, const char *fragCode);

        Location addMatrixInput(std::string name);

        void setMatrixInput(Location loc, ccCore::Matrix4f mat);

        Location addTextureInput(std::string name);

        void addBufferInput(std::string name, unsigned int index);

        void set();

        void unload();

    private:
        GLuint shaderProgram;

        void printShaderInfoLog(GLuint obj);
        void printProgramInfoLog(GLuint obj);

        [[nodiscard]] static std::string_view getTypeName(GLenum type);
    };

    class SubMesh {
    public:
        enum Primitives {
            TRIANGLES = GL_TRIANGLES,
            LINES = GL_LINES
        };

        void beginLoad();

        void addBuffer(Shader::Location loc, const float *data, unsigned int dataSize, unsigned int size);

        void endLoad(Primitives primitives, unsigned int count);

        void endLoadWithIndex(Primitives primitives, unsigned int count, const unsigned int *data);

        void draw();

        void unload();

    private:
        GLuint mId;
        Primitives mPrimitives;
        unsigned int mCount;
        bool mWithIndex;
    };
}
