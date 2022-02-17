#pragma once
#include "framework.h"
#include "Engine.h"

class DoubleBuffering
{
public:
	DoubleBuffering();
	~DoubleBuffering();

	void DrawGameObjects(HDC hdc, Gdiplus::Graphics&);
};

