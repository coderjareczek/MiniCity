#pragma once

#include "infrastructure.h"
#include "string"

template <typename T>
class Zone : public Infrastructure
{
	T characteristic_value;
	std::string characteristic_description;
	virtual void generate_characteristic_value() = 0;
public:
	Zone(char s, T c_v, std::string c_d) : Infrastructure(s), characteristic_value(c_v), characteristic_description(c_d) {}
	
	void set_characteristic_value(T c_v)
	{
		characteristic_value = c_v;
	}

	void set_characteristic_description(std::string s)
	{
		characteristic_description = s;
	}

	T get_characteristic_value()
	{
		return characteristic_value;
	}

};