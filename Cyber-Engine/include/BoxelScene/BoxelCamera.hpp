#pragma once

#include "../Math.hpp"

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
  math::Vector3f mPosition;
  math::Vector2f mAngle;
  
  bool mActionRotateUp, mActionRotateDown, mActionRotateLeft, mActionRotateRight, mActionMoveForward, mActionMoveBackward;
};
