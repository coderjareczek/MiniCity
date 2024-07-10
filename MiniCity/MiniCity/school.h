#pragma once

#include "infrastructure.h"
#include "special_element.h"

class School : public Infrastructure, public Special_element
{
	const int maintenance_cost = 300;
public:
	School(char s = 'S') : Infrastructure(s) {}
};