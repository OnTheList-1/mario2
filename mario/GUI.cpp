#include "GUI.h"
#include "Resource.h"
#include "Collision.h"
#include "Character.h"
#include <string>
#include "Engine.h"

GUI::GUI()
{
	stage = 1;
	lives = 5;
	coins = 0;
	atPortal = false;
}

GUI::~GUI()
{

}

void GUI::Draw(Gdiplus::Graphics& graphics)
{
	Gdiplus::FontFamily fontFamily(L"Verdana");
	Gdiplus::Font font(&fontFamily, 20, Gdiplus::FontStyleRegular, Gdiplus::Unit::UnitPixel);
	Gdiplus::PointF livesTextPos(10, 0);
	Gdiplus::PointF livesNumberPos(75, 0);
	Gdiplus::PointF coinsTextPos(10, 20);
	Gdiplus::PointF coinsNumberPos(75, 20);
	Gdiplus::SolidBrush solidBrush(Gdiplus::Color(0, 0, 0));

	std::wstring livesToWchar = std::to_wstring(lives);
	std::wstring coinsToWchar = std::to_wstring(coins);
	// Draw Lives
	graphics.DrawString(L"Lives: ", -1, &font, livesTextPos, &solidBrush);
	graphics.DrawString(livesToWchar.c_str(), -1, &font, livesNumberPos, &solidBrush);

	// Draw Coins
	graphics.DrawString(L"Coins: ", -1, &font, coinsTextPos, &solidBrush);
	graphics.DrawString(coinsToWchar.c_str(), -1, &font, coinsNumberPos, &solidBrush);

	if (atPortal)
	{
		++stage;
		atPortal = false;
	}

	// Draw Stage
	if (hasLives() == false)
	{
		Gdiplus::PointF gameOverPos(350, 10);
		graphics.DrawString(L"Game Over", -1, &font, gameOverPos, &solidBrush);
	}
	else
	{
		Gdiplus::PointF roundPos(350, 10);
		Gdiplus::PointF roundPos2(450, 10);
		std::wstring stageToWChar = std::to_wstring(stage);

		graphics.DrawString(L"Round ", -1, &font, roundPos, &solidBrush);
		graphics.DrawString(stageToWChar.c_str(), -1, &font, roundPos2, &solidBrush);
	}

}

bool GUI::hasLives()
{
	return lives > 0;
}

void GUI::addCoins(const int& coin)
{
	coins += coin;
}

void GUI::completeRound()
{
	atPortal = true;
}

void GUI::removeLife()
{
	if (lives > 0)
		--lives;
}

void GUI::ResetRound()
{
	stage = 1;
}

void GUI::ResetCoins()
{
	coins = 0;
}

void GUI::ResetLives()
{
	lives = 5;
}