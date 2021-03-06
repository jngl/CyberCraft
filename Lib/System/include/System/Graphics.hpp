#pragma once

#include <System/GraphicsData.h>

#include <Core/Math.h>
#include <Core/Id.h>

#include <Kernel/Texture.h>

#include "System/Common.h"

#include "glad/glad.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace cs {
    class Shader;
//
//    class MeshBuilder;
    class ShaderBuilder;
//
//    using IdValue = unsigned int;
//
//    struct MeshId : public cc::Id<IdValue, struct MeshIdTag> {};
//    struct ShaderId : public cc::Id<IdValue, struct ShaderIdTag> {};
//
//    struct DrawCommand {
//        ShaderId shader;
//        MeshId mesh;
//        cc::Matrix4f transform;
//    };
//
//    class DrawCommandList {
//    public:
//        void add(DrawCommand cmd);
//    };
//
    class GraphicsContext : public ck::TextureManager
    {
    public:
        GraphicsContext();

        [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename) override;
        void loadTexture(ck::TextureHandle handle) override;
        void unloadTexture(ck::TextureHandle handle) override;

        void setCurrentTexture(ck::TextureHandle);
        [[nodiscard]] ck::TextureHandle getCurrentTexture() const;

//        MeshId loadMesh(const MeshBuilder& builder);
//        void unloadMesh(MeshId mesh);

//        ShaderId loadShader(const ShaderBuilder& builder);
//        void unloadShader(std::unique_ptr<Shader> shader);

//        void draw(DrawCommandList& cmdList);

    private:
        struct Texture{
            unsigned int glId = 0;
            std::string fileName;
        };

        cc::IdGenerator<ck::TextureHandle::ValueType, ck::TextureHandle::Tag> m_textureIdGenerator;
        std::vector<Texture> m_textures;

        ck::TextureHandle m_current_texture;
    };


    class Shader {
    public:
        typedef uint Location;

        void load(const char *vertCode, const char *fragCode);

        Location addMatrixInput(const std::string& name);

        void setMatrixInput(Location loc, cc::Matrix4f mat);

//        Location addTextureInput(const std::string& name);

        void addBufferInput(const std::string& name, unsigned int index);

        void set();

//        void unload();

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
