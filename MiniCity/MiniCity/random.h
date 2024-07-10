#pragma once

#include <random>

class Random
{
public:
	int rand_int(int low, int high)
	{
		static std::default_random_engine re{ std::random_device{}() };
		using Dist = std::uniform_int_distribution<int>;
		static Dist uid{};
		return uid(re, Dist::param_type{ low,high });
	}
};