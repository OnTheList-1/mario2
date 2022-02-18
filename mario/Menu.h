#pragma once
#include "framework.h"

class Menu
{
public:
	Menu();
	void CreateMenu(const HWND&, Gdiplus::Graphics&);
	void ToggleMenu(const bool& flag, const HWND&);
	bool getGameState() const;
	void setGameState(const bool&);

private:
	HBITMAP START_BUTTON;
	HBITMAP EXIT_BUTTON;

	bool GameState; // True if in game, false if at menu
};