#include "Setting.h"
#include "Character.h"
#include "Engine.h"
#include "framework.h"
#include "State.h"

Character::Character()
{
	charBitmap = nullptr;
	prevPosition.x = 0;
	prevPosition.x = 0;

	position.x = 150;
	position.y = RESOLUTION_Y - 250;

	speed.x = 0;
	speed.y = 0;

	GoesLeft = false;
	GoesRight = false;

	isFaceFoward = true;
	dead = false;
}


HBITMAP Character::getBitmap()
{
	return charBitmap;
}

bool Character::IsDead()
{
	return this->dead;
}

void Character::Logic(const double& delta, State* state)
{
	if (!dead)
	{
		// save previous position
		prevPosition = position;

		// update x position and make sure we don't go out of bound
		position.x += speed.x * delta;
		if (position.x < CHARACTER_WIDTH / 2)
		{
			position.x = CHARACTER_WIDTH / 2;
			speed.x = 0;
		}
		if (position.x > PLATFORM_WIDTH * TILE_WIDTH - CHARACTER_WIDTH / 2)
		{
			position.x = PLATFORM_WIDTH * TILE_WIDTH - CHARACTER_WIDTH / 2;
			speed.x = 0;
		}
		if (GoesLeft)
		{ //if left key is pressed
			speed.x -= 1000 * delta;
			if (speed.x < -200)
				speed.x = -200;
		}
		if (GoesRight)
		{ // if right key is pressed
			speed.x += 1000 * delta;
			if (speed.x > 200)
				speed.x = 200;
		}
		if (!GoesLeft && !GoesRight)
		{ // create drag so character will stop
			if (speed.y == 0)
			{
				if (speed.x > 0)
				{
					speed.x -= 1000 * delta;
					if (speed.x < 10)
						speed.x = 0;
				}
				if (speed.x < 0)
				{
					speed.x += 1000 * delta;
					if (speed.x > -10)
						speed.x = 0;
				}
			}
		}

		// if on air then fall
		position.y += speed.y * delta;
		speed.y += 1000 * delta;

		if (speed.x > 0) // if speed isn't negative face foward 
			isFaceFoward = true;
		if (speed.x < 0) // else no
			isFaceFoward = false;
	}
	else
	{ // if dead then float up
		position.y -= 200 * delta;

	}

}

void Character::Jump(const bool& flag)
{
	if (!dead)
	{
		if (flag)
			speed.y = -535;
		else
			speed.y = -400;
	}
}

void Character::topCollision()
{ // top collision
	if (!dead)
		speed.y = abs(speed.y);
}

void Character::leftCollision(const double& pos)
{ // left collision
	if (!dead)
	{
		speed.x = 0;
		position.x += pos;
	}
}

void Character::rightCollision(const double& pos)
{ // right collision
	if (!dead)
	{
		speed.x = 0;
		position.x -= pos;
	}
}

void Character::setDead()
{ // kill the character
	dead = true;
}

void Character::reset()
{
	position.x = 150;
	position.y = RESOLUTION_Y - 250;

	speed.x = 0;
	speed.y = 0;

	GoesLeft = false;
	GoesRight = false;

	isFaceFoward = true;
	dead = false;
}

void Character::bottomCollision(const double& pos)
{ // bottom collision
	if (!dead)
	{
		speed.y = 0;
		position.y -= pos;
	}
}

void Character::Draw(Gdiplus::Graphics& graphics)
{
	Gdiplus::Image imgCharacter(L"maincharacter.png");
	Gdiplus::Graphics g(&imgCharacter);


	// Determine the state of character to draw
	int posX = 1;
	int posY = 1;
	int sprite_gap_x = 1;
	int off_set_running_backward = 0;
	int dead_sprite_gap = 0;

	// If character is facing foward
	if (isFaceFoward)
	{
		if ((position.y != prevPosition.y))
		{ // if character in a jump
			posX = 1;
			posY = 360;
		}

		else if (position.x == prevPosition.x)
		{ //if character isn't moving
			posX = rand() % 3 + 1;
			posY = 1;
			sprite_gap_x = 75;
		}

		else if (position.x != prevPosition.x)
		{ // if character is moving on the ground
			posY = 120;
			posX = (int)position.x % 100 / 33;
			sprite_gap_x = 80;
		}

		if (dead)
		{
			posX = 190;
			posY = 530;
			dead_sprite_gap = 30;
		}
	}

	// If character is facing backward
	else
	{
		if ((position.y != prevPosition.y))
		{ // if character is in a jump
			posX = 500;
			posY = 360;
		}

		else if ((position.x == prevPosition.x))
		{ // if character isn't moving
			posX = rand() % 3 + 4;
			posY = 1;
			sprite_gap_x = 75;

		}

		else if ((position.x != prevPosition.x))
		{ // if character is moving on the ground
			posY = 120;
			posX = (int)position.x % 100 / 33;
			sprite_gap_x = 80;
			off_set_running_backward = 240;
		}

		if (dead)
		{
			posX = 300;
			posY = 530;
			dead_sprite_gap = 30;
		}
	}

	// Destination Rect (window screen position)
	Gdiplus::Rect destinationRect(int(position.x - Engine::offset - CHARACTER_WIDTH / 2), int(position.y - CHARACTER_TILE_HEIGHT),
		CHARACTER_WIDTH + dead_sprite_gap, CHARACTER_HEIGHT + 10);


	// Draw Image into the buffer
	graphics.DrawImage(&imgCharacter,
		destinationRect,
		off_set_running_backward + posX * sprite_gap_x, posY,
		CHARACTER_WIDTH + dead_sprite_gap, CHARACTER_HEIGHT,
		Gdiplus::Unit::UnitPixel);
}
