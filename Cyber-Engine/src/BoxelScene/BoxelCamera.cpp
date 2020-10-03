#include "BoxelScene/BoxelCamera.hpp"

#include "Window.hpp"

BoxelCamera::BoxelCamera():
mActionRotateUp(false),
mActionRotateDown(false),
mActionRotateLeft(false),
mActionRotateRight(false),
mActionMoveForward(false),
mActionMoveBackward(false)
{
  mRendererCamera = Renderer::createCamera();
  Renderer::setActiveCamera(mRendererCamera);
  
  mDist=60.f;
}

void BoxelCamera::addAction(Window& window){
	window.addAction(SDL_SCANCODE_W, &mActionMoveForward, true);
	window.addAction(SDL_SCANCODE_S, &mActionMoveBackward, true);
	window.addAction(SDL_SCANCODE_UP, &mActionRotateUp, true);
	window.addAction(SDL_SCANCODE_DOWN, &mActionRotateDown, true);
	window.addAction(SDL_SCANCODE_LEFT, &mActionRotateLeft, true);
	window.addAction(SDL_SCANCODE_RIGHT, &mActionRotateRight, true);
}
  
void BoxelCamera::update(float frameTime){
    const float moveSpeed = frameTime*15.f;
    const float rotateSpeed = frameTime*1.56f;

    math::Vector3f moveVec(cos(mAngle.x)*cos(mAngle.y), sin(mAngle.x), cos(mAngle.x)*sin(mAngle.y));
    
    if(mActionMoveForward){
      mPosition += moveVec*moveSpeed;
    }else if(mActionMoveBackward){
      mPosition -= moveVec*moveSpeed;
    }else if(mActionRotateRight){
      mAngle.y += rotateSpeed;
    }else if(mActionRotateLeft){
      mAngle.y -= rotateSpeed;
    }else if(mActionRotateUp){
      mAngle.x += rotateSpeed;
    }else if(mActionRotateDown){
      mAngle.x -= rotateSpeed;
    }
    
    math::Matrix4f viewMatrix;

    viewMatrix.lookAt(mPosition, mPosition+moveVec, {0.f, 1.0f, 0.f});
    
    Renderer::getCameraViewMatrixRef(mRendererCamera) = viewMatrix;
}
