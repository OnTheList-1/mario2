#pragma once

#include "Resource.h"
#include "EngineBase.h"
#include "Platform.h"
#include "Character.h"
#include "GUI.h"
#include "State.h"
#include "Monster.h"
#include <irrKlang.h>


class Engine : public EngineBase
{
public:
	Engine();
	~Engine();

	void KeyUp(WPARAM, State*);
	void KeyDown(WPARAM);

	void LoadMonsters(const int& stage);
	void ClearMonsters();
	void Logic(const double& delta, State*) override;

	static double offset;
private:
	Platform* platform;
	Character* character;
	Monster* monsters[MONSTER_POPULATION]; // maximum 6 monsters by default
	int numberOfMonsters;

	GUI* gui;

	bool leftKeyPressed;
	bool rightKeyPressed;
	bool spaceKeyPressed;
};