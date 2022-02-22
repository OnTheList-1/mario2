#pragma once

#include "resource.h"
#include "framework.h"
#include "State.h"

class Menu
{
public:
	Menu();
	~Menu();

	void CreateMenu(const HWND&, Gdiplus::Graphics&);
	void CreateGameOverMenu(const HWND&, Gdiplus::Graphics&);

	void KeyDown(WPARAM, State*);

private:
	const WCHAR* buttonImg;

	bool startButtonSelected;
	bool settingButtonSelected;
	bool exitButtonSelected;

	bool gameoverRestartSelected;
	bool gameoverExitSelected;
};