#include "Setting.h"
#include "Collision.h"
#include "Character.h"
#include "Platform.h"
#include "Engine.h"

Platform::Platform()
{
	tileSetImg = nullptr;
	cloudsImg = nullptr;

	// empty map
	for (int i = 0; i < PLATFORM_HEIGHT; ++i)
	{
		for (int j = 0; j < PLATFORM_WIDTH; ++j)
		{
			PlatformMatrix[i][j] = -1;
			PlatformSolids[i][j] = false;
		}
	}

	// Load map from file
	std::ifstream my_file("level.txt");
	if (my_file.is_open())
	{
		for (int i = 0; i < PLATFORM_HEIGHT; ++i)
		{
			for (int j = 0; j < PLATFORM_WIDTH; ++j)
			{
				my_file >> PlatformMatrix[i][j];
				PlatformSolids[i][j] = tileIsSolid(PlatformMatrix[i][j]);
			}
		}
	}
	else
		MessageBox(nullptr, L"Can't find file to load map.", nullptr, MB_OK);

}

bool Platform::tileIsSolid(const int& tileNumber)
{
	for (int i = 0; i < 34; ++i)
	{
		if (solids[i] == tileNumber)
			return true;
	}
	return false;
}

Collision Platform::CharacterCollide(Character* character)
{
	int numberOfCollision = 0;
	Collision collisions[9];
	Collision cummulatedCollision;

	cummulatedCollision.top = 0;
	cummulatedCollision.bottom = 0;
	cummulatedCollision.left = 0;
	cummulatedCollision.right = 0;

	double charTop = character->getPosition().y - CHARACTER_HEIGHT;
	double charBottom = character->getPosition().y;
	double charLeft = character->getPosition().x - CHARACTER_WIDTH / 2 + 3;
	double charRight = character->getPosition().x + CHARACTER_WIDTH / 2 - 4;

	// check the tile around character
	int startX = (int)(charLeft / TILE_WIDTH);
	int startY = (int)(charTop / TILE_WIDTH);
	int endX = (int)(charRight / TILE_WIDTH);
	int endY = (int)(charBottom / TILE_WIDTH);

	if (startX < 0)
		startX = 0;
	if (startY < 0)
		startY = 0;
	if (endX > PLATFORM_WIDTH - 1)
		endX = PLATFORM_WIDTH - 1;
	if (endY > PLATFORM_HEIGHT - 1)
		endY = PLATFORM_HEIGHT - 1;

	for (int i = startY; i <= endY; ++i)
	{
		for (int j = startX; j <= endX; ++j)
		{
			if (PlatformSolids[i][j])
			{
				double tileTop = i * TILE_WIDTH;
				double tileBottom = (i + 1) * TILE_WIDTH - 1;
				double tileLeft = j * TILE_WIDTH;
				double tileRight = (j + 1) * TILE_WIDTH - 1;

				// If it's a collision
				if (charTop < tileBottom && charBottom > tileTop && charRight > tileLeft && charLeft < tileRight)
				{
					// add this collision to the list
					collisions[numberOfCollision].top = abs(charTop - tileBottom);
					collisions[numberOfCollision].bottom = abs(charBottom - tileTop);
					collisions[numberOfCollision].left = abs(charLeft - tileRight);
					collisions[numberOfCollision].right = abs(charRight - tileLeft);

					collisions[numberOfCollision].keepSmallest();

					// add the collision details to the cummulated collision
					cummulatedCollision.top += collisions[numberOfCollision].top;
					cummulatedCollision.bottom += collisions[numberOfCollision].bottom;
					cummulatedCollision.left += collisions[numberOfCollision].left;
					cummulatedCollision.right += collisions[numberOfCollision].right;

					++numberOfCollision;
				}
			}
		}
	}

	// whichever side collides the most, that side is taken into consideration
	cummulatedCollision.keepLargest();
	if (cummulatedCollision.top != 0)
	{
		cummulatedCollision.top = 0;
		for (int i = 0; i < numberOfCollision; ++i)
			cummulatedCollision.top = fmax(cummulatedCollision.top, collisions[i].top);

	}
	if (cummulatedCollision.bottom != 0)
	{
		cummulatedCollision.bottom = 0;
		for (int i = 0; i < numberOfCollision; ++i)
			cummulatedCollision.bottom = fmax(cummulatedCollision.bottom, collisions[i].bottom);

	}
	if (cummulatedCollision.left != 0)
	{
		cummulatedCollision.left = 0;
		for (int i = 0; i < numberOfCollision; ++i)
			cummulatedCollision.left = fmax(cummulatedCollision.left, collisions[i].left);

	}
	if (cummulatedCollision.right != 0)
	{
		cummulatedCollision.right = 0;
		for (int i = 0; i < numberOfCollision; ++i)
			cummulatedCollision.right = fmax(cummulatedCollision.right, collisions[i].right);

	}

	return cummulatedCollision;
}

void Platform::Draw(Gdiplus::Graphics& graphics)
{
	// Initialize Images for graphics
	Gdiplus::Image cloudImg(L"clouds.png");
	Gdiplus::Image tilesetImg(L"tileset.png");

	// Draw the clouds and offset it by half to create a moving screen
	int start_x = int(Engine::offset / 2.0);
	while (start_x > RESOLUTION_X)
		start_x -= RESOLUTION_X;

	graphics.DrawImage(&cloudImg,
		0 - start_x, 0,
		RESOLUTION_X - start_x, RESOLUTION_Y);

	graphics.DrawImage(&cloudImg,
		RESOLUTION_X - start_x, 0,
		2 * RESOLUTION_X - start_x, RESOLUTION_Y);

	//if (tileSetImg == nullptr) // load image if it hasn't been loaded
	//	tileSetImg = engine->LoadImageW(L"tileset.png");
	//if (cloudsImg == nullptr)
	//	cloudsImg = engine->LoadImageW(L"clouds.png");
	//// Draw the clouds and offset it by half to create a moving screen
	//int start_x = int(Engine::offset / 2.0);
	//while (start_x > RESOLUTION_X)
	//	start_x -= RESOLUTION_X;


	//HBITMAP hNewBmp1 = nullptr;
	//HBITMAP hNewBmp2 = nullptr;
	//HDC compDc1;
	//HDC compDc2;
	//BITMAP bmp1;
	//BITMAP bmp2;

	//compDc1 = CreateCompatibleDC(hdc);
	//compDc2 = CreateCompatibleDC(hdc);
	//hNewBmp1 = (HBITMAP)SelectObject(compDc1, tileSetImg);
	//hNewBmp2 = (HBITMAP)SelectObject(compDc2, cloudsImg);

	//if (tileSetImg && cloudsImg)
	//{
	//	SetMapMode(hdc, GetMapMode(hdc));
	//	GetObject(tileSetImg, sizeof(BITMAP), (LPSTR)&bmp1);
	//	GetObject(cloudsImg, sizeof(BITMAP), (LPSTR)&bmp2);

	//	BitBlt(hdc,
	//		0 - start_x, 0,
	//		RESOLUTION_X - start_x, RESOLUTION_Y,
	//		compDc2,
	//		0, 10,
	//		SRCCOPY); // draw cloud

	//	BitBlt(hdc,
	//		RESOLUTION_X - start_x, 0,
	//		2 * RESOLUTION_X - start_x, RESOLUTION_Y,
	//		compDc2,
	//		0, 0,
	//		SRCCOPY); //draw cloud

	//	// Draw tiles
	//	for (int i = 0; i < PLATFORM_HEIGHT; i++)
	//	{
	//		for (int j = 0; j < PLATFORM_WIDTH; j++)
	//		{
	//			if ((j + 1) * TILE_WIDTH >= Engine::offset && j * TILE_WIDTH < Engine::offset + RESOLUTION_X)
	//			{
	//				if (PlatformMatrix[i][j] != -1)
	//				{

	//					int posY = PlatformMatrix[i][j] / 7;
	//					int posX = PlatformMatrix[i][j] % 7;

	//					BitBlt(hdc,
	//						int(j * TILE_WIDTH - Engine::offset), i * TILE_WIDTH,
	//						TILE_WIDTH, 50,
	//						compDc1,
	//						posX * TILE_WIDTH, posY * TILE_WIDTH,
	//						SRCCOPY);
	//				}
	//			}
	//		}
	//	}
	//	SelectObject(compDc1, hNewBmp1);
	//	SelectObject(compDc2, hNewBmp2);
	//}
	//DeleteDC(compDc1);
	//DeleteDC(compDc2);
}