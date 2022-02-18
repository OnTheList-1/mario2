#include "framework.h"
#include "Platform.h"
#include "Setting.h"
#include "EngineBase.h"
#include "Engine.h"

double Engine::offset = 0;

Engine::Engine()
{
	// Initialize Character
	character = new Character();
	AddGameObject(character);

	// Initialize Platform
	platform = new Platform();
	AddGameObject(platform);

	leftKeyPressed = false;
	rightKeyPressed = false;
	spaceKeyPressed = false;
}

Engine::~Engine()
{
}

void Engine::KeyDown(WPARAM wParam)
{
	if (wParam == VK_LEFT)
		leftKeyPressed = true;
	if (wParam == VK_RIGHT)
		rightKeyPressed = true;
	if (wParam == VK_SPACE)
		spaceKeyPressed = true;
}

void Engine::KeyUp(WPARAM wParam)
{
	if (wParam == VK_LEFT)
		leftKeyPressed = false;
	if (wParam == VK_RIGHT)
		rightKeyPressed = false;
	if (wParam == VK_SPACE)
		spaceKeyPressed = false;
}

void Engine::Logic(const double& delta)
{
	EngineBase::Logic(delta);

	if (!character->IsDead())
	{ // character isn't dead we go in here

		character->GoesLeft = leftKeyPressed;
		character->GoesRight = rightKeyPressed;

		// Pick up coins
		platform->CollectCoins(character);

		// if we collide with tiles
		Collision cd = platform->CharacterCollide(character);
		if (cd.bottom > 0)
		{ // bottom collision
			character->bottomCollision(cd.bottom);
			if (spaceKeyPressed)
			{ // jump
				character->Jump(true);
				spaceKeyPressed = false;
			}

		}
		if (cd.left > 0) // left collision
			character->leftCollision(cd.left);

		if (cd.right > 0) // right collision
			character->rightCollision(cd.right);

		if (cd.top > 0) // top collision
			character->topCollision();

		if (character->getPosition().y > RESOLUTION_Y) // check if user is off the platform
		{
			character->setDead();
		}

		// this creates the camera effect
		Engine::offset = character->getPosition().x - RESOLUTION_X / 2;
		if (Engine::offset < 0)
			Engine::offset = 0;
		if (Engine::offset > PLATFORM_WIDTH * TILE_WIDTH - RESOLUTION_X)
			Engine::offset = PLATFORM_WIDTH * TILE_WIDTH - RESOLUTION_X;

	}
	else
	{ // if character is dead then it float up
		if (character->getPosition().y < 0)
			character->reset();
	}

}