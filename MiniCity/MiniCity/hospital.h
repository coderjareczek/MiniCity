#pragma once

#include "infrastructure.h"
#include "special_element.h"

class Hospital : public Infrastructure, public Special_element
{
	const int maintenance_cost = 800;
public:
	Hospital(char s = 'M') : Infrastructure(s) {}
};