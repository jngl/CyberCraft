#pragma once

#include "Scene.hpp"

class BasicScene : public Scene
{
public:
	BasicScene();
	
	void addAction(Window& window) override;
	
	void update(float frameTime) override;
	
private:
};
