#pragma once

#include "Scene.hpp"

class BasicScene : public Scene
{
public:
	void addAction(cc::System::Window& window) override;
	void update(float frameTime) override;
	
private:
};
