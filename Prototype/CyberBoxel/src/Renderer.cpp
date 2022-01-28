/********************************************************
 * Includes
********************************************************/

#include "Renderer.hpp"

#include "CyberBase/PoolAllocator.hpp"

#include "System/DdsFile.h"

#include <CyberBase/Log.hpp>

#include <memory>
#include <set>
#include <vector>
#include <algorithm>

/********************************************************
 * Sprite Mesh Data
********************************************************/

constexpr unsigned int spriteVerticesNumber = 4;
constexpr unsigned int spriteVerticesDimension = 4;
constexpr unsigned int spriteVerticesTextureDimension = 4;
constexpr unsigned int spriteFacesNumber = 2;

constexpr std::array<float, spriteVerticesNumber*spriteVerticesDimension> spriteVertices =
        {0.f, 0.f, 0.f,
         0.f, 1.f, 0.f,
         1.f, 1.f, 0.f,
         1.f, 0.f, 0.f};

constexpr std::array<float, spriteVerticesNumber*spriteVerticesTextureDimension> spriteTexCoord =
        {0.f, 0.f,
         0.f, 1.f,
         1.f, 1.f,
         1.f, 0.f};


constexpr std::array<unsigned int, spriteFacesNumber*3> spriteFaces = {0, 1, 2, 0, 2, 3};


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

    cs::Shader defaultShader;
    cs::Shader noLightShader;
    cs::Shader defaultNoTextureShader;

    const unsigned int VertexBufferIndex = 0;
    const unsigned int TexCoordBufferIndex = 1;
    const unsigned int NormalBufferIndex = 2;

    cs::Shader::Location defaultShaderMVP;
    cs::Shader::Location noLightShaderMVP;
    cs::Shader::Location defaultNoTextureShaderMVP;

    cs::Mesh spriteMesh;

    float ratio;

    struct Material {
        const cp::Texture* texture = nullptr;

        bool withAlpha = false;
        std::string name;
    };

    struct Camera {
        static constexpr float fov = 45.f;
        static constexpr float near = 0.1f;
        static constexpr float far = 1000.f;

        cc::Matrix4f mViewMatrix;
        bool perspective = true;

        [[nodiscard]] cc::Matrix4f getProjectionMatrix() const {
            cc::Matrix4f proj;

            if (perspective) {
                proj.projectPerspective(fov, ratio, near, far);
            } else {
                const float zoom = 10.f;
                proj.projectOrthographic(-zoom, zoom, -zoom, zoom, -far, far);
            }

            return proj;
        }
    };

    std::vector<std::unique_ptr<Camera>> cameraArray;
    Camera_handle activeCamera;

    struct Model {
        std::string nom;
        std::vector<cs::Mesh> subMeshs;
        std::vector<Material_handle> materials;
    };

    std::set<Object *> objectArray;

    struct Sprite {
        const cp::Texture* mTexture;

        cc::Matrix4f mMatrix;
    };

/********************************************************
 * Renderer function
********************************************************/

    static std::unique_ptr<cs::GraphicsContext> g_graphicsContext;

    void createRenderer() {
        CB_LOG_INFO << "Renderer construct";

        g_graphicsContext = std::make_unique<cs::GraphicsContext>();

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
        spriteMesh.addBuffer(0, spriteVertices.data(),
                             sizeof(spriteVertices), 3);
        spriteMesh.addBuffer(1, spriteTexCoord.data(),
                             sizeof(spriteTexCoord), 2);
        spriteMesh.endLoadWithIndex(cs::Mesh::TRIANGLES, spriteFacesNumber * 3,
                                    spriteFaces.data());
    }

    void destroyRenderer() {
        CB_LOG_INFO << "Renderer destruct";
        g_graphicsContext.reset();
    }

    void resize(int width, int height) {
        resizeAllCamera(width, height);
    }

/********************************************************
 * Material
********************************************************/
    constexpr int maxNumberOfMaterial = 100;
    cc::PoolAllocator<Material, maxNumberOfMaterial> MaterialPool;

    Material_handle createMaterial(const cp::Texture& tex, std::string_view name) {

        CB_LOG_INFO <<"Renderer : create material \"" + std::string(name) + "\"";
        Material_handle result = MaterialPool.create();
        result->texture = &tex;
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
    constexpr int MaxNumberOfModel = 100;
    cc::PoolAllocator<Model, MaxNumberOfModel> ModelPool;

    Model_handle createModel(std::string_view nom) {
        CB_LOG_INFO << "Renderer create model \"" + std::string(nom) + "\"";
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

        model->subMeshs.emplace_back();

        cs::Mesh &subMesh = model->subMeshs.back();

        if (material->texture == nullptr) {
            subMesh.beginLoad();
            subMesh.addBuffer(0, vertices,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.addBuffer(2, normals,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.endLoadWithIndex(cs::Mesh::TRIANGLES, nbFaces * 3,
                                     faces);
        } else {
            subMesh.beginLoad();
            subMesh.addBuffer(0, vertices,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.addBuffer(1, texCoord,
                              nbVertices * sizeof(float) * 2, 2);
            subMesh.addBuffer(2, normals,
                              nbVertices * sizeof(float) * 3, 3);
            subMesh.endLoadWithIndex(cs::Mesh::TRIANGLES, nbFaces * 3,
                                     faces);
        }
    }

    void destroyModel(Model_handle handle) {
        CB_LOG_INFO << "Renderer : destroy model \"" + handle->nom + "\"";
        for(auto& mesh: handle->subMeshs){
            mesh.unload();
        }
        ModelPool.destroy(handle);
    }


/********************************************************
 * Objects
********************************************************/

    void renderAllObject2(bool alpha) {
        for (Object *object : objectArray) {
            cc::Matrix4f VP = activeCamera->getProjectionMatrix() * activeCamera->mViewMatrix;
            if (object->model != nullptr) {
                cc::Matrix4f MVP = VP * object->matrix;

                Model_handle model = object->model;
                for (std::size_t i(0); i < model->subMeshs.size(); ++i) {
                    if (model->materials[i]->withAlpha == alpha) {
                        if (model->materials[i]->texture == nullptr) {
                            defaultNoTextureShader.set();
                            defaultNoTextureShader.setMatrixInput(defaultNoTextureShaderMVP, MVP);
                        } else {
                            defaultShader.set();
                            defaultShader.setMatrixInput(defaultShaderMVP, MVP);

                            g_graphicsContext->setCurrentTexture(model->materials[i]->texture);
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

    Object::Object(std::string_view objectName) :
            model(nullptr),
            name(objectName) {
        CB_LOG_INFO << "Renderer : create object \"" + name + "\"";
        objectArray.insert(this);
    }

    Object::~Object() {
        CB_LOG_INFO << "Renderer : destroy object";
        objectArray.erase(this);
    }

    /********************************************************
     * Textures
    ********************************************************/

    std::shared_ptr<cp::Texture> loadTextureFromFile(std::string_view filename){
        return g_graphicsContext->loadTextureFromFile(filename);
    }

/********************************************************
 * Camera
********************************************************/
    Camera_handle createCamera() {
        CB_LOG_INFO << "Renderer create camera";
        auto newCamera = std::make_unique<Camera>();
        Camera_handle result = newCamera.get();
        result->perspective = true;
        cameraArray.push_back(std::move(newCamera));
        return result;
    }

    void destroyCamera(Camera_handle handle) {
        auto it = std::find_if(cameraArray.begin(), cameraArray.end(), [handle](const std::unique_ptr<Camera>& cam){
            return cam.get() == handle;
        });
        cameraArray.erase(it);
    }

    cc::Matrix4f &getCameraViewMatrixRef(Camera_handle handle) {
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
    constexpr int MaxNumberOfSprite = 1000;
    cc::PoolAllocator<Sprite, MaxNumberOfSprite> SpritePool;

    Sprite_handle createSprite(const cp::Texture& handle) {
        CB_LOG_INFO << "Renderer create sprite";
        Sprite_handle result = SpritePool.create();
        result->mMatrix.setIdentity();
        result->mTexture = &handle;
        return result;
    }

    void destroySprite(Sprite_handle sprite) { SpritePool.destroy(sprite); }

    cc::Matrix4f &getSpriteMatrixRef(Sprite_handle handle) {
        return handle->mMatrix;
    }

    void renderSprite(Sprite_handle handle) {
        cc::Matrix4f MVP = activeCamera->getProjectionMatrix() *
                               activeCamera->mViewMatrix * handle->mMatrix;

        noLightShader.set();
        noLightShader.setMatrixInput(noLightShaderMVP, MVP);

        g_graphicsContext->setCurrentTexture(handle->mTexture);

        spriteMesh.draw();
    }
}
