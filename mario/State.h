#pragma once

#include "framework.h"
class State
{
public:
	State();
	~State();
	void setState(const int&);
	int getState() const;
private:
	int state;
};