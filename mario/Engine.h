#pragma once

#include "Resource.h"
#include "EngineBase.h"
#include "Platform.h"
#include "Character.h"
#include "GUI.h"
#include "State.h"
#include "State.h"

class Engine : public EngineBase
{
public:
	Engine();
	~Engine();

	void KeyUp(WPARAM, State*);
	void KeyDown(WPARAM);

	void Logic(const double& delta, State*) override;

	static double offset;
private:
	Platform* platform;
	Character* character;
	GUI* gui;

	bool leftKeyPressed;
	bool rightKeyPressed;
	bool spaceKeyPressed;
};