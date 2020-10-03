#pragma once

#include "Scene.hpp"

class BasicScene : public Scene
{
public:
	void addAction(Window& window) override;
	void update(float frameTime) override;
	
private:
};
