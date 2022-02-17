#include "Setting.h"
#include "Character.h"
#include "Engine.h"
#include "framework.h"

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

void Character::Logic(const double& delta)
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
					speed.x -= 500 * delta;
					if (speed.x < 10)
						speed.x = 0;
				}
				if (speed.x < 0)
				{
					speed.x += 500 * delta;
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

void Character::LoadBitmap(const LPCWSTR& file_path)
{
	Gdiplus::GdiplusStartupInput gpStartupInput;
	ULONG_PTR gpToken;
	GdiplusStartup(&gpToken, &gpStartupInput, NULL);
	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(file_path, false);
	if (bitmap)
	{
		bitmap->GetHBITMAP(Gdiplus::Color(255, 255, 255), &charBitmap);
		delete bitmap;
	}
	Gdiplus::GdiplusShutdown(gpToken);
}

void Character::Jump(const bool& flag)
{
	if (!dead)
	{
		if (flag)
			speed.y = -700;
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
	Gdiplus::Image imgCharacter(L"characters.png");

	graphics.DrawImage(&imgCharacter, int(position.x - Engine::offset - CHARACTER_WIDTH / 2), int(position.y - CHARACTER_TILE_HEIGHT), CHARACTER_WIDTH, CHARACTER_HEIGHT);


	/*LoadBitmapW(L"characters.png");
	if (!charBitmap)
		MessageBox(nullptr, L"Can't locate character bitmap", nullptr, 0);


	HBITMAP hNewBmp = nullptr;
	HDC compDc;
	BITMAP bmp;

	compDc = CreateCompatibleDC(hdc);
	hNewBmp = charBitmap;
	SelectObject(compDc, charBitmap);

	if (charBitmap)
	{
		SetMapMode(hdc, GetMapMode(hdc));
		GetObject(charBitmap, sizeof(BITMAP), (LPSTR)&bmp);


		BitBlt(hdc,
			int(position.x - Engine::offset - CHARACTER_WIDTH / 2), int(position.y - CHARACTER_TILE_HEIGHT), CHARACTER_WIDTH, CHARACTER_TILE_HEIGHT,
			compDc,
			0, 0,
			SRCAND);

		BitBlt(hdc,
			0, CHARACTER_TILE_HEIGHT, CHARACTER_WIDTH, CHARACTER_TILE_HEIGHT,
			compDc,
			0, 0,
			SRCPAINT);


		SelectObject(compDc, hNewBmp);
	}
	DeleteDC(compDc);*/

}


//Gdiplus::GdiplusStartupInput gdiplusStartupInput;
//ULONG_PTR gdiplusToken;
//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

//Gdiplus::Graphics graphics(hdc);
//Gdiplus::Image* image = new Gdiplus::Image(L"characters.png");

//if (image == nullptr)
//	MessageBox(nullptr, L"Can't locate the image", nullptr, 0);

//graphics.DrawImage(image, CHARACTER_WIDTH, CHARACTER_HEIGHT);

//delete image;
//Gdiplus::GdiplusShutdown(gdiplusToken);
