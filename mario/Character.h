#pragma once
#include "resource.h"
#include "framework.h"
#include "EngineBase.h"
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character();

	HBITMAP getBitmap();

	void Logic(const double&) override;
	void Draw(Gdiplus::Graphics&) override;

	void Jump(const bool&);
	void bottomCollision(const double& pos);
	void leftCollision(const double& pos);
	void rightCollision(const double& pos);
	void topCollision();
	void setDead();
	void reset();

	bool IsDead();

	bool GoesLeft;
	bool GoesRight;

private:
	HBITMAP charBitmap;

	Point speed;
	Point prevPosition;

	bool dead;
	bool isFaceFoward;

};