#pragma once

#include <System/GraphicsData.h>

#include <Core/Math.h>
#include "System/Common.h"
#include <Core/Id.h>

#include "glad/glad.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace cc::System {
    class Texture;
    class Shader;

    class MeshBuilder;
    class ShaderBuilder;

    struct TextureId : public ccCore::Id {};
    struct MeshId : public ccCore::Id {};
    struct ShaderId : public ccCore::Id {};

    struct DrawCommand {
        ShaderId shader;
        MeshId mesh;
        ccCore::Matrix4f transform;
    };

    class DrawCommandList {
    public:
        void add(DrawCommand cmd);
    };

    class GraphicsContext
    {
    public:
        GraphicsContext();

        std::shared_ptr<Texture> loadTexture(std::string_view filename);

        void setCurrentTexture(const std::shared_ptr<Texture> &texture);
        [[nodiscard]]std::weak_ptr<Texture> getCurrentTexture();

        TextureId loadTexture(const TextureData& builder);
        void unloadTexture(TextureId id);

        MeshId loadMesh(const MeshBuilder& builder);
        void unloadMesh(MeshId mesh);

        ShaderId loadShader(const ShaderBuilder& builder);
        void unloadShader(std::unique_ptr<Shader> shader);

        void draw(DrawCommandList& cmdList);

    private:
        std::unordered_map<std::string, std::weak_ptr<Texture>> m_textures;
        std::weak_ptr<Texture> m_current_texture;
    };


    class Shader {
    public:
        typedef unsigned int Location;

        void load(const char *vertCode, const char *fragCode);

        Location addMatrixInput(const std::string& name);

        void setMatrixInput(Location loc, ccCore::Matrix4f mat);

        Location addTextureInput(const std::string& name);

        void addBufferInput(const std::string& name, unsigned int index);

        void set();

        void unload();

    private:
        GLuint shaderProgram = 0;

        static void printShaderInfoLog(GLuint obj);
        static void printProgramInfoLog(GLuint obj);

        [[nodiscard]] static std::string_view getTypeName(GLenum type);
    };

    class  Mesh {
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
