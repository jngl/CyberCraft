#pragma once

#include <Core/Math.h>

#include "../Renderer.hpp"

#include "../Window.hpp"

class BoxelCamera
{
public:
  BoxelCamera();
  
  void addAction(Window& window);
  
  void update(float frameTime);
  
private:
  Renderer::Camera_handle mRendererCamera;

  float mDist;
    ccCore::Vector3f mPosition;
    ccCore::Vector2f mAngle;
  
  bool mActionRotateUp, mActionRotateDown, mActionRotateLeft, mActionRotateRight, mActionMoveForward, mActionMoveBackward;
};
