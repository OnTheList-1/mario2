#pragma once

class EngineBase;

#include "Resource.h"
#include "EngineBase.h"
#include "Point.h"

class GameObject
{
public:
	virtual void Logic(const double& delta) {};
	virtual void Draw(Gdiplus::Graphics&) {};

	Point getPosition();

	EngineBase* engine;
protected:
	Point position;
};