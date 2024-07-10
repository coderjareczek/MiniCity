#pragma once

#include <map>

class Infrastructure
{
	const char symbol;
	static std::map<char, int> number_of_elements;
protected:
	Infrastructure(char s) : symbol(s)
	{
		number_of_elements[s]++;
	}
public:
	Infrastructure() : Infrastructure(' ') {}

	virtual ~Infrastructure() = default;

	char get_symbol() const
	{
		return symbol;
	}

	static std::map<char, int> get_number_of_elements_map()
	{
		return number_of_elements;
	}

	static int get_number_of(char s) 
	{
		return number_of_elements[s];
	}
};