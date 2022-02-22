#include "framework.h"
#include "Platform.h"
#include "Setting.h"
#include "EngineBase.h"
#include "Engine.h"
#include "GUI.h"
#include "Monster.h"

double Engine::offset = 0;

Engine::Engine()
{
	// Initialize Character
	character = new Character();
	AddGameObject(character);

	// Initialize Platform
	platform = new Platform();
	AddGameObject(platform);

	// Initialize Monsters
	LoadMonsters(platform->GetStage());

	// Initialize GUI
	gui = new GUI();
	AddGameObject(gui);



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

void Engine::KeyUp(WPARAM wParam, State* state)
{
	if (wParam == VK_LEFT)
		leftKeyPressed = false;
	if (wParam == VK_RIGHT)
		rightKeyPressed = false;
	if (wParam == VK_SPACE)
		spaceKeyPressed = false;
	if (wParam == VK_ESCAPE)
		state->setState(0);
}

void Engine::LoadMonsters(const int& stage)
{
	switch (stage)
	{ // Load in different monsters' attribute depending on the stage
	case 0: // stage 1
		numberOfMonsters = 4;
		monsters[0] = new Monster(480, 350, 570, 1);
		AddGameObject(monsters[0]);
		monsters[1] = new Monster(1475, 150, 1525, 0);
		AddGameObject(monsters[1]);
		monsters[2] = new Monster(3275, 300, 3475, 1);
		AddGameObject(monsters[2]);
		monsters[3] = new Monster(2500, 250, 2700, 7);
		AddGameObject(monsters[3]);
		break;

	case 1: // stage 2
		numberOfMonsters = 4;
		monsters[0] = new Monster(1020, 400, 1085, 0);
		AddGameObject(monsters[0]);
		monsters[1] = new Monster(1300, 350, 1525, 7);
		AddGameObject(monsters[1]);
		monsters[2] = new Monster(3305, 300, 3460, 1);
		AddGameObject(monsters[2]);
		monsters[3] = new Monster(3810, 350, 3970, 7);
		AddGameObject(monsters[3]);
		break;

	case 2: // stage 3
		numberOfMonsters = 4;
		monsters[0] = new Monster(1085, 350, 1220, 0);
		AddGameObject(monsters[0]);
		monsters[1] = new Monster(1300, 350, 1525, 7);
		AddGameObject(monsters[1]);
		monsters[2] = new Monster(3305, 350, 3460, 1);
		AddGameObject(monsters[2]);
		monsters[3] = new Monster(3810, 350, 3970, 7);
		AddGameObject(monsters[3]);
		break;
	}
}

void Engine::ClearMonsters()
{
	for (int i = 0; i < numberOfMonsters; ++i)
	{
		RemoveGameObject(monsters[i]);
	}

}

void Engine::Logic(const double& delta, State* state)
{
	EngineBase::Logic(delta, state);

	if (state->getState() == 1)
	{ // check state first

		if (!character->IsDead())
		{ // character isn't dead we go in here

			character->GoesLeft = leftKeyPressed;
			character->GoesRight = rightKeyPressed;

			// Pick up coins
			gui->addCoins(platform->CollectCoins(character));

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

			for (int i = 0; i < numberOfMonsters; ++i)
			{ // check for collision with monsters
				Collision cd = monsters[i]->CharacterCollide(character);
				if (cd.bottom > 0)
				{ // if we jump and landed on a monster
					Monster* oldMonster = monsters[i];
					for (int j = i; j < numberOfMonsters - 1; ++j)
					{
						monsters[j] = monsters[j + 1];
					}
					monsters[numberOfMonsters - 1] = nullptr;
					RemoveGameObject(oldMonster);
					delete oldMonster;
					//oldMonster = nullptr;
					--numberOfMonsters;
					character->Jump(false);
				}
				else if (cd.left > 0 || cd.right > 0 || cd.top > 0)
				{
					character->setDead();
					gui->removeLife();
				}
			}

			if (character->getPosition().y > RESOLUTION_Y) // check if user is off the platform
			{
				character->setDead();
				gui->removeLife();
			}

			if (platform->AtPortal(character))
			{ // if character is at portal
				gui->completeRound();
				platform->NextRound();
				platform->LoadNextMap(platform->GetStage());
				ClearMonsters();
				LoadMonsters(platform->GetStage());
				character->reset();
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
			if (character->getPosition().y < 0 && gui->hasLives())
				character->reset();
			else if (gui->hasLives() == false)
			{ // reset map & update stage
				gui->ResetRound();
				gui->ResetCoins();
				gui->ResetLives();
				state->setState(2);
				platform->ResetGame();
				platform->LoadNextMap(platform->GetStage());
				ClearMonsters();
				LoadMonsters(platform->GetStage());
				character->reset();
			}
		}
	}
}