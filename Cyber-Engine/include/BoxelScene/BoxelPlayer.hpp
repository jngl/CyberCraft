#pragma once

#include "Renderer.hpp"
#include "Window.hpp"

class BoxelPlayer
{
public:
  BoxelPlayer();

  void addAction(Window& window);

private:
  Renderer::Object mObject;
};
