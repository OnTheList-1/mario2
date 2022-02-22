#include "Monster.h"
#include "Engine.h"

Monster::Monster(const double& initialX, const double& initialY, const double& maxX, const int& type)
{
	position.x = initialX;
	position.y = initialY;

	minXDistance = initialX;
	maxXDistance = maxX;

	MonsterType = type;

	isFaceFoward = true;
}

Monster::~Monster()
{
}

Collision Monster::CharacterCollide(Character* character)
{
	double charTop = character->getPosition().y - CHARACTER_HEIGHT;
	double charBottom = character->getPosition().y;
	double charLeft = character->getPosition().x - CHARACTER_WIDTH / 2 + 3;
	double charRight = character->getPosition().x + CHARACTER_WIDTH / 2 - 4;

	double monsterTop = position.y - MONSTER_HEIGHT;
	double monsterBottom = position.y;
	double monsterLeft = position.x - MONSTER_WIDTH / 2 + 3;
	double monsterRight = position.x + MONSTER_WIDTH / 2 - 4;

	Collision collision;

	collision.top = 0;
	collision.bottom = 0;
	collision.left = 0;
	collision.right = 0;

	if (charTop < monsterBottom && charBottom > monsterTop && charRight > monsterLeft && charLeft < monsterRight)
	{
		collision.top = abs(charTop - monsterBottom);
		collision.bottom = abs(charBottom - monsterTop);
		collision.left = abs(charLeft - monsterRight);
		collision.right = abs(charRight - monsterLeft);

		collision.keepSmallest();
	}
	return collision;
}

void Monster::Logic(const double& delta, State* state)
{ // monster walk along x-axis between minxdistance and maxxdistance
	position.x += (isFaceFoward ? 25 : -25) * delta;

	if (position.x >= maxXDistance)
		isFaceFoward = false;

	if (position.x <= minXDistance)
		isFaceFoward = true;
}

void Monster::Draw(Gdiplus::Graphics& graphics)
{
	Gdiplus::Image monsterImg(L"monster.png");

	Gdiplus::Rect destinationRect(
		(int)position.x - Engine::offset - MONSTER_WIDTH / 2, (int)position.y - MONSTER_HEIGHT,
		MONSTER_WIDTH, MONSTER_HEIGHT);

	int posX = (int)position.x % 20 / 10 + (isFaceFoward ? 2 : 0);
	int posY = MonsterType;

	graphics.DrawImage(&monsterImg, destinationRect,
		posX * MONSTER_WIDTH, posY * MONSTER_HEIGHT,
		MONSTER_WIDTH, MONSTER_HEIGHT,
		Gdiplus::Unit::UnitPixel);

}
