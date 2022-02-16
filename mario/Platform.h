#pragma once

class Character;

#include "Setting.h"
#include "Resource.h"
#include "framework.h"
#include "Collision.h"
#include "EngineBase.h"
#include "GameObject.h"

class Platform : public GameObject
{
public:
	Platform();

	void Draw(HDC) override;

	Collision CharacterCollide(Character* character);

private:
	int PlatformMatrix[PLATFORM_HEIGHT][PLATFORM_WIDTH];
	int PlatformSolids[PLATFORM_HEIGHT][PLATFORM_WIDTH];

	bool tileIsSolid(const int& tileNumber);

	int solids[34] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16, 17, 18, 19, 20, 24, 25, 26, 27, 31, 32, 33, 34, 41, 42, 43, 44, 49, 50 };

	HBITMAP tileSetImg;
	HBITMAP cloudsImg;
};