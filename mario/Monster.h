#pragma once
#include "framework.h"

#include "Character.h"
#include "Collision.h"
#include "EngineBase.h"
#include "GameObject.h"

/*
	Monster type

	1 - Flying Monster
	2 - On ground Monster

*/

class Monster : public GameObject
{
public:
	Monster(const double&, const double&, const double&, const int&);
	~Monster();

	void Logic(const double&, State*) override;
	void Draw(Gdiplus::Graphics&) override;

	Collision CharacterCollide(Character* character);

private:
	double minXDistance;
	double maxXDistance;

	int MonsterType;

	bool isFaceFoward;

};

