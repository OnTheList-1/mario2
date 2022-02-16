#pragma once

#include "Resource.h"
#include "EngineBase.h"
#include "Platform.h"
#include "Character.h"

class Engine : public EngineBase
{
public:
	Engine();
	~Engine();

	void KeyUp(WPARAM);
	void KeyDown(WPARAM);

	void Logic(const double& delta) override;

	static double offset;
private:
	Platform* platform;
	Character* character;

	bool leftKeyPressed;
	bool rightKeyPressed;
	bool spaceKeyPressed;
};