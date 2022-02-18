#include "Menu.h"
#include "Resource.h"

Menu::Menu()
{
	START_BUTTON = nullptr;
	EXIT_BUTTON = nullptr;
	GameState = false;

}

void Menu::CreateMenu(const HWND& hwnd, Gdiplus::Graphics& graphics)
{
	// Get cursor's position
	POINT mousePosition;
	GetCursorPos(&mousePosition);
	ScreenToClient(hwnd, &mousePosition);

	// Load in image
	Gdiplus::Image* button = new Gdiplus::Image(L"buttons.png");

	// Check event
	if (mousePosition.x > 0 && mousePosition.x < 50 &&
		mousePosition.y > 0 && mousePosition.y < 50)
	{
		Gdiplus::Rect destinationRect(250, 250,
			70, 240);


		// Draw Image into the buffer
		graphics.DrawImage(gbutton,
			destinationRect,
			200, 200,
			70, 100,
			Gdiplus::Unit::UnitPixel);
		graphics.DrawImage(button, 0, 0, 50, 50);
	}
	else
	{
		graphics.DrawImage(button, 0, 0, 50, 50);
	}

	delete button;
	button = nullptr;

	//ReleaseDC(nextTurnButtonWindow, nextTurnButtonDC);
}

void Menu::ToggleMenu(const bool& flag, const HWND& hwnd)
{

	//InvalidateRect(hwnd, nullptr, false);
}

void Menu::setGameState(const bool& flag)
{
	GameState = flag;
}

bool Menu::getGameState() const
{
	return GameState;
}

