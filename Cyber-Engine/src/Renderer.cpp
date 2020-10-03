/********************************************************
 * Includes
********************************************************/

#include "Renderer.hpp"

#include "PoolAllocator.hpp"

#include "debugAssert.hpp"

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

std::string defaultShaderVert =
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

std::string defaultShaderFrag =
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

std::string noLightShaderVert =
  "#version 150\n"
  "in vec3 inPosition;\n"
  "in vec2 inTexCoord;\n"
  "uniform mat4 MVP; \n"
  "out vec2 texCoord;\n"
  "void main() {\n"
  "    gl_Position = MVP*vec4(inPosition,1);\n"
  "    texCoord = inTexCoord;\n"
  "}\n";

std::string noLightShaderFrag =
  "#version 150\n"
  "in vec2 texCoord;\n"
  "out vec4 outBuffer;\n"
  "uniform sampler2D textureSampler;\n"
  "void main(){\n"
  "    vec3 color = texture( textureSampler, texCoord ).rgb;\n"
  "    outBuffer=vec4(color, 1.0);\n"
  "}\n";

std::string defaultNoTextureShaderVert =
  "#version 150\n"
  "in vec3 inPosition;\n"
  "in vec3 inNormal;\n"
  "uniform mat4 MVP; \n"
  "out vec3 normal;\n"
  "void main() {\n"
  "    gl_Position = MVP*vec4(inPosition,1);\n"
  "    normal = inNormal;\n"
  "}\n";

std::string defaultNoTextureShaderFrag =
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

  Graphics::Shader defaultShader;
  Graphics::Shader noLightShader;
  Graphics::Shader defaultNoTextureShader;

  const unsigned int VertexBufferIndex = 0;
  const unsigned int TexCoordBufferIndex = 1;
  const unsigned int NormalBufferIndex = 2;

  Graphics::Shader::Location defaultShaderMVP;
  Graphics::Shader::Location noLightShaderMVP;
  Graphics::Shader::Location defaultNoTextureShaderMVP;

  Graphics::SubMesh spriteMesh;

  float ratio;

  struct Material {
    Texture_handle texture;
    bool withAlpha;
    std::string name;
  };

  struct Camera {
    math::Matrix4f mViewMatrix;
    bool perspective;
    math::Matrix4f getProjectionMatrix(){
      math::Matrix4f proj;
      
      if (perspective) {
	proj.projectPerspective(45, ratio, 0.1f, 1000);
      } else {
	const float zoom = 10.f;
	proj.projectOrthographic(-zoom, zoom, -zoom, zoom, -1000, 1000);
      }
      
      return proj;
    }
  };
  std::set<Camera*> cameraArray;
  Camera_handle activeCamera;

  struct Model {
    std::string nom;
    std::vector<Graphics::SubMesh> subMeshs;
    std::vector<Material_handle> materials;
  };

  std::set<Object*> objectArray;

  struct Sprite {
    Texture_handle mTexture;
    math::Matrix4f mMatrix;
  };

/********************************************************
 * Renderer function
********************************************************/

  void createRenderer() {
    debug::log("Renderer", "construct");

    Graphics::createGraphics();

    // noTexture
    defaultNoTextureShader.load(defaultNoTextureShaderVert.c_str(),
				defaultNoTextureShaderFrag.c_str());
    defaultNoTextureShader.addBufferInput("inPosition", VertexBufferIndex);
    defaultNoTextureShader.addBufferInput("inNormal", NormalBufferIndex);
    defaultNoTextureShaderMVP = defaultNoTextureShader.addMatrixInput("MVP");

    // default
    defaultShader.load(defaultShaderVert.c_str(), defaultShaderFrag.c_str());
    defaultShader.addBufferInput("inPosition", VertexBufferIndex);
    defaultShader.addBufferInput("inTexCoord", TexCoordBufferIndex);
    defaultShader.addBufferInput("inNormal", NormalBufferIndex);
    defaultShaderMVP = defaultShader.addMatrixInput("MVP");

    // sprite
    noLightShader.load(noLightShaderVert.c_str(), noLightShaderFrag.c_str());
    noLightShader.addBufferInput("inPosition", VertexBufferIndex);
    noLightShader.addBufferInput("inTexCoord", TexCoordBufferIndex);
    noLightShaderMVP = noLightShader.addMatrixInput("MVP");

    // sprite mesh
    spriteMesh.beginLoad();
    spriteMesh.addBuffer(0, spriteVertices,
			 sizeof(spriteVertices), 3);
    spriteMesh.addBuffer(1, spriteTexCoord,
			 sizeof(spriteTexCoord), 2);
    spriteMesh.endLoadWithIndex(Graphics::SubMesh::TRIANGLES, spriteNbFaces * 3,
				spriteFaces);
  }

  void destroyRenderer() {
	  debug::log("Renderer", "destruct"); 
	  Graphics::destroyGraphics();
  }

  void resize(int width, int height) {
    resizeAllCamera(width, height);
  }

/********************************************************
 * Material
********************************************************/
  core::PoolAllocator<Material, 100> MaterialPool;

  Material_handle createMaterial(Texture_handle tex, std::string name) {
    debug::log("Renderer", "create materia \"", name, "\"");
    Material_handle result = MaterialPool.create();
    result->texture = tex;
    result->withAlpha = false;
    result->name = name;
    return result;
  }

  void destroyMaterial(Material_handle handle) { MaterialPool.destory(handle); }

  void setWithAlpha(Material_handle handle, bool alpha){
    handle->withAlpha = alpha;
  }
/********************************************************
 * Models
********************************************************/
  core::PoolAllocator<Model, 100> ModelPool;

  Model_handle createModel(std::string nom){
    debug::log("Renderer", "create model \"", nom, "\"");
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
		  Material_handle material)
  {
    model->materials.push_back(material);

    model->subMeshs.push_back(Graphics::SubMesh());

    Graphics::SubMesh& subMesh = model->subMeshs.back();
    
    if (material->texture == nullptr) {
      subMesh.beginLoad();
      subMesh.addBuffer(0, vertices,
				nbVertices * sizeof(float) * 3, 3);
      subMesh.addBuffer(2, normals,
				nbVertices * sizeof(float) * 3, 3);
      subMesh.endLoadWithIndex(Graphics::SubMesh::TRIANGLES, nbFaces * 3,
				       faces);
    } else {
      subMesh.beginLoad();
      subMesh.addBuffer(0, vertices,
				nbVertices * sizeof(float) * 3, 3);
      subMesh.addBuffer(1, texCoord,
				nbVertices * sizeof(float) * 2, 2);
      subMesh.addBuffer(2, normals,
				nbVertices * sizeof(float) * 3, 3);
      subMesh.endLoadWithIndex(Graphics::SubMesh::TRIANGLES, nbFaces * 3,
				       faces);
    }
  }

  void destoryModel(Model_handle handle) {
    debug::log("Renderer", "destroy model \"", handle->nom, "\"");
    for(std::size_t i(0); i<handle->subMeshs.size(); ++i){
      handle->subMeshs[i].unload();
    }
    ModelPool.destory(handle);
  }

  

/********************************************************
 * Objects
********************************************************/

  void renderAllObject2(bool alpha){
    for (Object *object : objectArray) {
      math::Matrix4f VP = activeCamera->getProjectionMatrix() * activeCamera->mViewMatrix;
      if(object->model){
	math::Matrix4f MVP = VP  * object->matrix;

	Model_handle model = object->model;
	for(std::size_t i(0); i<model->subMeshs.size(); ++i){
	  if(model->materials[i]->withAlpha==alpha){
	    if(model->materials[i]->texture == nullptr){
	      defaultNoTextureShader.set();
	      defaultNoTextureShader.setMatrixInput(defaultNoTextureShaderMVP, MVP);
	    }else{
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
  Object::Object(std::string objectName):
    model(nullptr),
    name(objectName)
  {
    debug::log("Renderer", "create object \"", name, "\"");
    objectArray.insert(this);
  }

  Object::~Object(){
    debug::log("Renderer", "destory object");
    objectArray.erase(this);
  }
  
/********************************************************
 * Textures
********************************************************/

  std::set<Texture_handle> textures;
  //core::PoolAllocator<Graphics::Texture, 100> TexturePool;  

  Texture_handle createTexture(const char *filename) {
    debug::log("Renderer", "create texture \"", filename, "\"");

    for(Texture_handle texture : textures){
      if(texture->getName()==filename){
	return texture;
      }
    }

    Texture_handle result = new Graphics::Texture;
    textures.insert(result);
    result->load(filename);
    return result;
  }

  void destroyTexture(Texture_handle handle) {
    //TODO
  }

/********************************************************
 * Camera
********************************************************/
  Camera_handle createCamera() {
    debug::log("Renderer", "create camera");
    Camera_handle result = new Camera;
    result->perspective = true;
    cameraArray.insert(result);
    return result;
  }

  void destroyCamera(Camera_handle handle) { cameraArray.erase(handle); }

  math::Matrix4f &getCameraViewMatrixRef(Camera_handle handle) {
    return handle->mViewMatrix;
  }

  void setPerspective(Camera_handle handle, bool persp) {
    handle->perspective = persp;
  }

  void setActiveCamera(Camera_handle handle) { activeCamera = handle; }

  void resizeAllCamera(int width, int height) {
    ratio = static_cast<float>(width) /   static_cast<float>(height); 
  }

/********************************************************
 * Sprites
********************************************************/
  core::PoolAllocator<Sprite, 1000> SpritePool;

  Sprite_handle createSprite(Texture_handle handle) {
    debug::log("Renderer", "create sprite");
    Sprite_handle result = SpritePool.create();
    result->mMatrix.setIdentity();
    result->mTexture = handle;
    return result;
  }

  void destroySprite(Sprite_handle sprite) { SpritePool.destory(sprite); }

  math::Matrix4f &getSpriteMatrixRef(Sprite_handle handle) {
    return handle->mMatrix;
  }

  void renderSprite(Sprite_handle handle) {
    math::Matrix4f MVP = activeCamera->getProjectionMatrix() *
                       activeCamera->mViewMatrix * handle->mMatrix;

    noLightShader.set();
    noLightShader.setMatrixInput(noLightShaderMVP, MVP);

    handle->mTexture->set();

    spriteMesh.draw();
  }
}
