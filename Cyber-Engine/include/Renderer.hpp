#pragma once

#include "Graphics.hpp"

namespace Renderer {
  struct Material;
  struct Model;
   struct Camera;
  struct Sprite;

  typedef Material *Material_handle;
  typedef Graphics::Texture *Texture_handle;
  typedef Model *Model_handle;
  typedef Camera *Camera_handle;
  typedef Sprite *Sprite_handle;

  // main
  void createRenderer();
  void destroyRenderer();
  void resize(int width, int height);

  // material
  Material_handle createMaterial(Texture_handle tex, std::string name);
  void destroyMaterial(Material_handle handle);
  void setWithAlpha(Material_handle handle, bool alpha);

  // Model
  Model_handle createModel(std::string nom);
  void addSubMesh(Model_handle model, unsigned int nbVertices,
		  const float *vertices, const float *texCoord,
		  const float *normals, unsigned int nbFaces,
		  const unsigned int *faces, Material_handle material);
  void destoryModel(Model_handle handle);

  // Object
   void renderAllObject();

  struct Object{
    Object(std::string objectName);
    ~Object();
    
    Model_handle model;
    math::Matrix4f matrix;
    std::string name; 
  };
  
  // Texture
  Texture_handle createTexture(const char *filename);
  void destroyTexture(Texture_handle handle);

  // camera
  Camera_handle createCamera();
  void destroyCamera(Camera_handle handle);
  math::Matrix4f &getCameraViewMatrixRef(Camera_handle handle);
  void setPerspective(Camera_handle handle, bool persp);
  void setActiveCamera(Camera_handle handle);

  // sprite
  Sprite_handle createSprite(Texture_handle handle);
  void destroySprite(Sprite_handle sprite);
  math::Matrix4f &getSpriteMatrixRef(Sprite_handle handle);
  void renderSprite(Sprite_handle handle);
}
