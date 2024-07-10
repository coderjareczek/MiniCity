#pragma once

#include <algorithm>
#include "population_determinant.h"
#include "random.h"

class Population_determinant_tier_3 : public Population_determinant
{
	int find_interest(const int schools, const int hospitals) const override
	{
		Random random;
		return random.rand_int(5, 10) + schools * 3 + hospitals * 3;
	}
};
