#include "Menu.h"

Menu::Menu()
{
	buttonImg = L"buttons.png";

	startButtonSelected = true;
	settingButtonSelected = false;
	exitButtonSelected = false;

	gameoverRestartSelected = true;
	gameoverExitSelected = false;
}

Menu::~Menu()
{
}

void Menu::CreateMenu(const HWND& hwnd, Gdiplus::Graphics& graphics)
{
	// Load in image and create a pen for selected zone that wraps around the button
	Gdiplus::Image* button = new Gdiplus::Image(buttonImg);
	Gdiplus::Pen* blackPen = new Gdiplus::Pen(Gdiplus::Color(0, 0, 0), 5);

	// Create image buttons
	// Create Start Button & by default start button will be selected
	Gdiplus::Rect destinationRect(225, 50,
		350, 160);

	graphics.DrawImage(button,
		destinationRect, 70, 55, 350, 160,
		Gdiplus::Unit::UnitPixel);

	// Create Setting Button
	Gdiplus::Rect destinationRect1(225, 200, 350, 160);
	graphics.DrawImage(button,
		destinationRect1, 780, 270, 350, 160,
		Gdiplus::Unit::UnitPixel);

	// Create Quit Game Button
	Gdiplus::Rect destinationRect2(225, 360, 350, 160);
	graphics.DrawImage(button,
		destinationRect2, 785, 55, 350, 160,
		Gdiplus::Unit::UnitPixel);

	// Draw Selected Button
	if (startButtonSelected)
		graphics.DrawRectangle(blackPen, destinationRect);
	else if (settingButtonSelected)
		graphics.DrawRectangle(blackPen, destinationRect1);
	else if (exitButtonSelected)
		graphics.DrawRectangle(blackPen, destinationRect2);

	delete button;
	delete blackPen;
	button = nullptr;
	blackPen = nullptr;
	//ReleaseDC(nextTurnButtonWindow, nextTurnButtonDC);
}

void Menu::CreateGameOverMenu(const HWND& hwnd, Gdiplus::Graphics& graphics)
{
	Gdiplus::Image* button = new Gdiplus::Image(buttonImg);
	Gdiplus::Pen* blackPen = new Gdiplus::Pen(Gdiplus::Color(0, 0, 0));
	Gdiplus::FontFamily fontFamily(L"Verdana");
	Gdiplus::Font font(&fontFamily, 20, Gdiplus::FontStyleRegular, Gdiplus::Unit::UnitPixel);
	Gdiplus::Font fontSelected(&fontFamily, 30, Gdiplus::FontStyleBold, Gdiplus::Unit::UnitPixel);
	Gdiplus::SolidBrush solidBrush(Gdiplus::Color(0, 0, 0));

	Gdiplus::PointF restartPos(300, 300);
	Gdiplus::PointF exitPos(300, 400);

	if (gameoverRestartSelected)
	{

		graphics.DrawString(L"Restart", -1, &fontSelected, restartPos, &solidBrush);
		graphics.DrawString(L"Quit Game", -1, &font, exitPos, &solidBrush);
	}

	else if (gameoverExitSelected)
	{
		graphics.DrawString(L"Quit Game", -1, &fontSelected, exitPos, &solidBrush);
		graphics.DrawString(L"Restart", -1, &font, restartPos, &solidBrush);
	}
	delete blackPen;
	blackPen = nullptr;
}

void Menu::KeyDown(WPARAM wParam, State* state)
{
	switch (wParam)
	{
	case VK_DOWN:
		if (state->getState() == 0)
		{
			if (startButtonSelected)
			{
				startButtonSelected = false;
				settingButtonSelected = true;
			}
			else if (settingButtonSelected)
			{
				settingButtonSelected = false;
				exitButtonSelected = true;
			}
			else if (exitButtonSelected)
			{
				exitButtonSelected = false;
				startButtonSelected = true;
			}
		}
		else if (state->getState() == 2)
		{
			if (gameoverRestartSelected)
			{
				gameoverExitSelected = true;
				gameoverRestartSelected = false;
			}
			else if (gameoverExitSelected)
			{
				gameoverExitSelected = false;
				gameoverRestartSelected = true;
			}
		}

		break;

	case VK_UP:
		if (state->getState() == 0)
		{

			if (startButtonSelected)
			{
				exitButtonSelected = true;
				startButtonSelected = false;
			}
			else if (settingButtonSelected)
			{
				settingButtonSelected = false;
				startButtonSelected = true;
			}
			else if (exitButtonSelected)
			{
				exitButtonSelected = false;
				settingButtonSelected = true;
			}
		}
		else if (state->getState() == 2)
		{
			if (gameoverExitSelected)
			{
				gameoverExitSelected = false;
				gameoverRestartSelected = true;
			}
			else if (gameoverRestartSelected)
			{
				gameoverExitSelected = true;
				gameoverRestartSelected = false;
			}
		}
		break;

	case VK_RETURN:
		if (state->getState() == 0)
		{

			if (startButtonSelected)
			{
				state->setState(1);

			}
			else if (settingButtonSelected)
			{

			}
			else if (exitButtonSelected)
			{
				PostQuitMessage(0);
			}
		}
		else if (state->getState() == 2)
		{
			if (gameoverExitSelected)
				PostQuitMessage(0);
			else if (gameoverRestartSelected)
				state->setState(1);
		}
		break;

	}
}