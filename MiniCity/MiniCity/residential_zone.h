#pragma once

#include "zone.h"
#include "random.h"

class Residential_zone : public Zone<int>
{
	void generate_characteristic_value() override
	{
		Random random;
		int value = random.rand_int(10, 100);
		set_characteristic_value(value);
	}
public:
	Residential_zone(char s = 'r', int c_v = 1, std::string c_d = "tile value") : Zone(s, c_v, c_d) 
	{
		generate_characteristic_value();
	}
};