#include "DoubleBuffering.h"
#include "Engine.h"

DoubleBuffering::DoubleBuffering()
{
}

DoubleBuffering::~DoubleBuffering()
{
}

void DoubleBuffering::DrawGameObjects(HDC hdc, Gdiplus::Graphics& gBuffer)
{

	//Gdiplus::Bitmap* gpBitmap = new Gdiplus::Bitmap();
	// Create Buffer
	Gdiplus::Bitmap buffer(RESOLUTION_X, RESOLUTION_Y, PixelFormat32bppPARGB);
	Gdiplus::Graphics memGraphics(&buffer);
	Gdiplus::Bitmap* gpBitmap = new Gdiplus::Bitmap(L"clouds.png", false);

	// Main Window
	Gdiplus::Graphics graphics(hdc);

	// Draw images in memory buffer
	Gdiplus::Rect rect(0, 0, RESOLUTION_X, RESOLUTION_Y);
	memGraphics.DrawImage(gpBitmap, rect);


	// Draw image to the main screen
	gBuffer.DrawImage(&buffer, 0, 0);
}