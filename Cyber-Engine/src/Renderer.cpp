/********************************************************
 * Includes
********************************************************/

#include "Renderer.hpp"

#include "Core/PoolAllocator.hpp"

#include <Core/Debug.h>

#include <memory>
#include <set>
#include <vector>

/********************************************************
 * Sprite Mesh Data
********************************************************/

unsigned int spriteNbVertices = 4;
const float spriteVertices[] = {0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
                                1.f, 1.f, 0.f, 1.f, 0.f, 0.f};
const float spriteTexCoord[] = {0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f};
unsigned int spriteNbFaces = 2;
const unsigned int spriteFaces[] = {0, 1, 2, 0, 2, 3};

/********************************************************
 * Shaders sources
********************************************************/

constexpr const char* defaultShaderVert =
        "#version 150\n"
        "in vec3 inPosition;\n"
        "in vec2 inTexCoord;\n"
        "in vec3 inNormal;\n"
        "uniform mat4 MVP;\n"
        "out vec3 normal;\n"
        "out vec2 texCoord;\n"
        "void main() {\n"
        "    gl_Position = MVP*vec4(inPosition,1);\n"
        "    normal = inNormal;\n"
        "    texCoord = inTexCoord;\n"
        "}\n";

constexpr const char* defaultShaderFrag =
        "#version 150\n"
        "in vec3 normal;\n"
        "in vec2 texCoord;\n"
        "out vec4 outBuffer;\n"
        "uniform sampler2D textureSampler;\n"
        "void main(){\n"
        "    vec4 color = texture( textureSampler, texCoord ).rgba; \n"
        "    float light = 0.5 + max(dot(normalize(normal), normalize(vec3(1.0, "
        "0.5, 0.3))), 0.0);\n"
        "    outBuffer=vec4(color.xyz*light, color.a);\n"
        "}\n";

constexpr const char* noLightShaderVert =
        "#version 150\n"
        "in vec3 inPosition;\n"
        "in vec2 inTexCoord;\n"
        "uniform mat4 MVP; \n"
        "out vec2 texCoord;\n"
        "void main() {\n"
        "    gl_Position = MVP*vec4(inPosition,1);\n"
        "    texCoord = inTexCoord;\n"
        "}\n";

constexpr const char* noLightShaderFrag =
        "#version 150\n"
        "in vec2 texCoord;\n"
        "out vec4 outBuffer;\n"
        "uniform sampler2D textureSampler;\n"
        "void main(){\n"
        "    vec3 color = texture( textureSampler, texCoord ).rgb;\n"
        "    outBuffer=vec4(color, 1.0);\n"
        "}\n";

constexpr const char* defaultNoTextureShaderVert =
        "#version 150\n"
        "in vec3 inPosition;\n"
        "in vec3 inNormal;\n"
        "uniform mat4 MVP; \n"
        "out vec3 normal;\n"
        "void main() {\n"
        "    gl_Position = MVP*vec4(inPosition,1);\n"
        "    normal = inNormal;\n"
        "}\n";

constexpr const char* defaultNoTextureShaderFrag =
        "#version 150\n"
        "in vec3 normal;\n"
        "out vec4 outBuffer;\n"
        "void main(){\n"
        "    vec3 color =vec3(1.0);\n"
        "    float light = 0.5 + max(dot(normalize(normal), normalize(vec3(1.0, "
        "0.5, 0.3))), 0.0);\n"
        "    outBuffer=vec4(color*light, 1.0);\n"
        "}\n";

namespace Renderer {
/********************************************************
 * Definition
********************************************************/

    void resizeAllCamera(int width, int height);

    cc::System::Shader defaultShader;
    cc::System::Shader noLightShader;
    cc::System::Shader defaultNoTextureShader;

    const unsigned int VertexBufferIndex = 0;
    const unsigned int TexCoordBufferIndex = 1;
    const unsigned int NormalBufferIndex = 2;

    cc::System::Shader::Location defaultShaderMVP;
    cc::System::Shader::Location noLightShaderMVP;
    cc::System::Shader::Location defaultNoTextureShaderMVP;

    cc::System::SubMesh spriteMesh;

    float ratio;

    struct Material {
        Texture_handle texture;
        bool withAlpha;
        std::string name;
    };

    struct Camera {
        ccCore::Matrix4f mViewMatrix;
        bool perspective = true;

        [[nodiscard]] ccCore::Matrix4f getProjectionMatrix() const {
            ccCore::Matrix4f proj;

            if (perspective) {
                proj.projectPerspective(45, ratio, 0.1f, 1000);
            } else {
                const float zoom = 10.f;
                proj.projectOrthographic(-zoom, zoom, -zoom, zoom, -1000, 1000);
            }

            return proj;
        }
    };

    std::set<Camera *> cameraArray;
    Camera_handle activeCamera;

    struct Model {
        std::string nom;
        std::vector<cc::System::SubMesh> subMeshs;
        std::vector<Material_handle> materials;
    };

    std::set<Object *> objectArray;

    struct Sprite {
        Texture_handle mTexture;
        ccCore::Matrix4f mMatrix;
    };

/********************************************************
 * Renderer function
********************************************************/

    static std::unique_ptr<cc::System::GraphicsContext> g_graphicsContext;

    void createRenderer() {
        ccCore::log("Renderer", "construct");

        g_graphicsContext = std::make_unique<cc::System::GraphicsContext>();

        // noTexture
        defaultNoTextureShader.load(defaultNoTextureShaderVert,
                                    defaultNoTextureShaderFrag);
        defaultNoTextureShader.addBufferInput("inPosition", VertexBufferIndex);
        defaultNoTextureShader.addBufferInput("inNormal", NormalBufferIndex);
        defaultNoTextureShaderMVP = defaultNoTextureShader.addMatrixInput("MVP");

        // default
        defaultShader.load(defaultShaderVert, defaultShaderFrag);
        defaultShader.addBufferInput("inPosition", VertexBufferIndex);
        defaultShader.addBufferInput("inTexCoord", TexCoordBufferIndex);
        defaultShader.addBufferInput("inNormal", NormalBufferIndex);
        defaultShaderMVP = defaultShader.addMatrixInput("MVP");

        // sprite
        noLightShader.load(noLightShaderVert, noLightShaderFrag);
        noLightShader.addBufferInput("inPosition", VertexBufferIndex);
        noLightShader.addBufferInput("inTexCoord", TexCoordBufferIndex);
        noLightShaderMVP = noLightShader.addMatrixInput("MVP");

        // sprite mesh
        spriteMesh.beginLoad();
        spriteMesh.addBuffer(0, spriteVertices,
                             sizeof(spriteVertices), 3);
        spriteMesh.addBuffer(1, spriteTexCoord,
                             sizeof(spriteTexCoord), 2);
        spriteMesh.endLoadWithIndex(cc::System::SubMesh::TRIANGLES, spriteNbFaces * 3,
                                    spriteFaces);
    }

    void destroyRenderer() {
        ccCore::log("Renderer", "destruct");
        g_graphicsContext.reset();
    }

    void resize(int width, int height) {
        resizeAllCamera(width, height);
    }

/********************************************************
 * Material
********************************************************/
    ccCore::PoolAllocator<Material, 100> MaterialPool;

    Material_handle createMaterial(Texture_handle tex, std::string name) {
        ccCore::log("Renderer", "create materia \"", name, "\"");
        Material_handle result = MaterialPool.create();
        result->texture = tex;
        result->withAlpha = false;
        result->name = name;
        return result;
    }

    void destroyMaterial(Material_handle handle) { MaterialPool.destroy(handle); }

    void setWithAlpha(Material_handle handle, bool alpha) {
        handle->withAlpha = alpha;
    }

/********************************************************
 * Models
********************************************************/
    ccCore::PoolAllocator<Model, 100> ModelPool;

    Model_handle createModel(std::string nom) {
        ccCore::log("Renderer", "create model \"", nom, "\"");
        Model_handle result = ModelPool.create();
        result->nom = nom;
        return result;
    }

    void addSubMesh(Model_handle model,
                    unsigned int nbVertices,
                    const float *vertices,
                    const float *texCoord,
                    const float *normals,
                    unsigned int nbFaces,
                    const unsigned int *faces,
                    Material_handle material) {
        model->materials.push_back(material);

        model->subMeshs.push_back(cc::System::SubMesh());

        cc::System::SubMesh &subMesh = model->subMeshs.back();

        if (material->texture == nullptr) {
            subMesh.beginLoad();
            subMesh.addBuffer(0, vertices,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.addBuffer(2, normals,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.endLoadWithIndex(cc::System::SubMesh::TRIANGLES, nbFaces * 3,
                                     faces);
        } else {
            subMesh.beginLoad();
            subMesh.addBuffer(0, vertices,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.addBuffer(1, texCoord,
                              nbVertices * sizeof(float) * 2, 2);
            subMesh.addBuffer(2, normals,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.endLoadWithIndex(cc::System::SubMesh::TRIANGLES, nbFaces * 3,
                                     faces);
        }
    }

    void destroyModel(Model_handle handle) {
        ccCore::log("Renderer", "destroy model \"", handle->nom, "\"");
        for (std::size_t i(0); i < handle->subMeshs.size(); ++i) {
            handle->subMeshs[i].unload();
        }
        ModelPool.destroy(handle);
    }


/********************************************************
 * Objects
********************************************************/

    void renderAllObject2(bool alpha) {
        for (Object *object : objectArray) {
            ccCore::Matrix4f VP = activeCamera->getProjectionMatrix() * activeCamera->mViewMatrix;
            if (object->model) {
                ccCore::Matrix4f MVP = VP * object->matrix;

                Model_handle model = object->model;
                for (std::size_t i(0); i < model->subMeshs.size(); ++i) {
                    if (model->materials[i]->withAlpha == alpha) {
                        if (model->materials[i]->texture == nullptr) {
                            defaultNoTextureShader.set();
                            defaultNoTextureShader.setMatrixInput(defaultNoTextureShaderMVP, MVP);
                        } else {
                            defaultShader.set();
                            defaultShader.setMatrixInput(defaultShaderMVP, MVP);

                            model->materials[i]->texture->set();
                        }
                        model->subMeshs[i].draw();
                    }
                }
            }
        }
    }

    void renderAllObject() {
        renderAllObject2(false);
        renderAllObject2(true);
    }

    Object::Object(std::string objectName) :
            model(nullptr),
            name(objectName) {
        ccCore::log("Renderer", "create object \"", name, "\"");
        objectArray.insert(this);
    }

    Object::~Object() {
        ccCore::log("Renderer", "destory object");
        objectArray.erase(this);
    }

/********************************************************
 * Textures
********************************************************/

    std::set<Texture_handle> textures;
    //core::PoolAllocator<Graphics::Texture, 100> TexturePool;

    Texture_handle createTexture(std::string_view filename) {
        ccCore::log("Renderer", "create texture \"", filename, "\"");

        return g_graphicsContext->loadTexture(filename);
    }

/********************************************************
 * Camera
********************************************************/
    Camera_handle createCamera() {
        ccCore::log("Renderer", "create camera");
        Camera_handle result = new Camera;
        result->perspective = true;
        cameraArray.insert(result);
        return result;
    }

    void destroyCamera(Camera_handle handle) { cameraArray.erase(handle); }

    ccCore::Matrix4f &getCameraViewMatrixRef(Camera_handle handle) {
        return handle->mViewMatrix;
    }

    void setPerspective(Camera_handle handle, bool persp) {
        handle->perspective = persp;
    }

    void setActiveCamera(Camera_handle handle) { activeCamera = handle; }

    void resizeAllCamera(int width, int height) {
        ratio = static_cast<float>(width) / static_cast<float>(height);
    }

/********************************************************
 * Sprites
********************************************************/
    ccCore::PoolAllocator<Sprite, 1000> SpritePool;

    Sprite_handle createSprite(Texture_handle handle) {
        ccCore::log("Renderer", "create sprite");
        Sprite_handle result = SpritePool.create();
        result->mMatrix.setIdentity();
        result->mTexture = handle;
        return result;
    }

    void destroySprite(Sprite_handle sprite) { SpritePool.destroy(sprite); }

    ccCore::Matrix4f &getSpriteMatrixRef(Sprite_handle handle) {
        return handle->mMatrix;
    }

    void renderSprite(Sprite_handle handle) {
        ccCore::Matrix4f MVP = activeCamera->getProjectionMatrix() *
                               activeCamera->mViewMatrix * handle->mMatrix;

        noLightShader.set();
        noLightShader.setMatrixInput(noLightShaderMVP, MVP);

        handle->mTexture->set();

        spriteMesh.draw();
    }
}
