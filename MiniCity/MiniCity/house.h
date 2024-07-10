#pragma once

#include "building.h"

class House : public Building
{
public:
	House(char s = 'H') : Building(s) {}

};