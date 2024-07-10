#pragma once

#include "infrastructure.h"

class Road : public Infrastructure
{
public:
	Road(char s = 'R') : Infrastructure(s) {}
};