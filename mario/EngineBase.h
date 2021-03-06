#pragma once
#include "Resource.h"
#include "Point.h"
#include "GameObject.h"
#include "State.h"

class EngineBase
{
public:
	EngineBase();
	~EngineBase();

	void MousePosition(const int&, const int&);

	virtual void KeyUp(WPARAM);
	virtual void KeyDown(WPARAM);

	void AddGameObject(GameObject* gameObj);
	void RemoveGameObject(GameObject* gameObj);

	virtual void Logic(const double&, State*);
	void Draw(Gdiplus::Graphics&);

	HBITMAP LoadImage(const LPCWSTR&);

protected:
	Point mousePosition;

private:
	std::list<GameObject*> listObject;
};