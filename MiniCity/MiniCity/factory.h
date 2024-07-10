#pragma once

#include "building.h"

class Factory : public Building
{
public:
	Factory(char s = 'F') : Building(s) {}

};