#pragma once

#include <System/Graphics.hpp>

namespace Renderer {
    struct Material;
    struct Model;
    struct Camera;
    struct Sprite;

    using Material_handle = Material *;
    using Model_handle = Model *;
    using Camera_handle = Camera *;
    using Sprite_handle = Sprite *;

    // main
    void createRenderer();
    void destroyRenderer();

    void resize(int width, int height);

    // material
<<<<<<< HEAD:CyberBoxel/include/Renderer.hpp
    Material_handle createMaterial(ck::TextureHandle tex, std::string_view name);
=======
    Material_handle createMaterial(cc::TextureHandle tex, std::string_view name);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:Cyber-Engine/include/Renderer.hpp
    void destroyMaterial(Material_handle handle);

    void setWithAlpha(Material_handle handle, bool alpha);

    // Model
    Model_handle createModel(std::string_view nom);

    void addSubMesh(Model_handle model, unsigned int nbVertices,
                    const float *vertices, const float *texCoord,
                    const float *normals, unsigned int nbFaces,
                    const unsigned int *faces, Material_handle material);

    void destroyModel(Model_handle handle);

    // Object
    void renderAllObject();

    struct Object {
        Object(std::string_view objectName);

        ~Object();

        Model_handle model;
        cc::Matrix4f matrix;
        std::string name;
    };

    // TextureGL
<<<<<<< HEAD:CyberBoxel/include/Renderer.hpp
    [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename);
    void loadTexture(ck::TextureHandle handle);
    void unloadTexture(ck::TextureHandle handle);
=======
    [[nodiscard]] cc::TextureHandle getHandleFromFile(std::string_view filename);
    void loadTexture(cc::TextureHandle handle);
    void unloadTexture(cc::TextureHandle handle);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:Cyber-Engine/include/Renderer.hpp

    // camera
    Camera_handle createCamera();
    void destroyCamera(Camera_handle handle);

    cc::Matrix4f &getCameraViewMatrixRef(Camera_handle handle);

    void setPerspective(Camera_handle handle, bool persp);

    void setActiveCamera(Camera_handle handle);

    // sprite
<<<<<<< HEAD:CyberBoxel/include/Renderer.hpp
    Sprite_handle createSprite(ck::TextureHandle handle);
=======
    Sprite_handle createSprite(cc::TextureHandle handle);
>>>>>>> b0d8808aab9721dbaa8c9afaf9c8a706f1faee8f:Cyber-Engine/include/Renderer.hpp
    void destroySprite(Sprite_handle sprite);

    cc::Matrix4f &getSpriteMatrixRef(Sprite_handle handle);

    void renderSprite(Sprite_handle handle);
}
