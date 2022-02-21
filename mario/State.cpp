#include "State.h"

/*
	State = 0 -> at start menu
	State = 1 -> in game
	State = 2 -> Game Over
*/
State::State()
{
	state = 0;
}

State::~State()
{
}

void State::setState(const int& flag)
{
	state = flag;
}

int State::getState() const
{
	return state;
}