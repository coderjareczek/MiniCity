#pragma once

#include "infrastructure.h"

class Building : public Infrastructure
{
public:
	Building(char s) : Infrastructure(s) {}
};