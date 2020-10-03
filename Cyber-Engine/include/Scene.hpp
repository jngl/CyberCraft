#pragma once

#include "Window.hpp"

class Scene
{
public:
  virtual ~Scene(){}
	virtual void addAction(Window& window){};
	virtual void update(float frameTime) = 0;
};
