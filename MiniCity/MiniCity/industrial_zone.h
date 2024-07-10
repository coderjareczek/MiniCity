#pragma once

#include "zone.h"
#include "random.h"

class Industrial_zone: public Zone<double>
{
	void generate_characteristic_value() override
	{
		Random random;
		double value = random.rand_int(10, 100) / 10.0;
		set_characteristic_value(value);
	}
public:
	Industrial_zone(char s = 'i', double c_v = 1.0, std::string c_d = "air pollution") : Zone(s, c_v, c_d)
	{
		generate_characteristic_value();
	}
};