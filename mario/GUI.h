#pragma once
#include "resource.h"
#include "framework.h"
#include "EngineBase.h"
#include "GameObject.h"
#include "Platform.h"

class GUI : public GameObject
{
public:
	GUI();
	~GUI();

	void addCoins(const int& coins);
	bool hasLives();
	void removeLife();
	void ResetRound();
	void completeRound();
	void ResetCoins();
	void ResetLives();

	void Draw(Gdiplus::Graphics&) override;


private:

	int stage;
	int lives;
	int coins;
	bool atPortal;
};