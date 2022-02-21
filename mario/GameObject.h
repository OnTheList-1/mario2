#pragma once

class EngineBase;

#include "Resource.h"
#include "EngineBase.h"
#include "Point.h"
#include "State.h"

class GameObject
{
public:
	virtual void Logic(const double& delta, State*) {};
	virtual void Draw(Gdiplus::Graphics&) {};

	Point getPosition();

	EngineBase* engine;
protected:
	Point position;
};