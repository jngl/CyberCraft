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
    Material_handle createMaterial(ck::TextureHandle tex, std::string_view name);
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
    [[nodiscard]] ck::TextureHandle getHandleFromFile(std::string_view filename);
    void loadTexture(ck::TextureHandle handle);
    void unloadTexture(ck::TextureHandle handle);

    // camera
    Camera_handle createCamera();
    void destroyCamera(Camera_handle handle);

    cc::Matrix4f &getCameraViewMatrixRef(Camera_handle handle);

    void setPerspective(Camera_handle handle, bool persp);

    void setActiveCamera(Camera_handle handle);

    // sprite
    Sprite_handle createSprite(ck::TextureHandle handle);
    void destroySprite(Sprite_handle sprite);

    cc::Matrix4f &getSpriteMatrixRef(Sprite_handle handle);

    void renderSprite(Sprite_handle handle);
}
