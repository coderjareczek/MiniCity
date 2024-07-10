#include "city.h"

std::map<char, int> Infrastructure::number_of_elements;

City::City()
{
    layout.resize(dimensions.x);
    for (int i = 0; i < layout.size(); i++)
    {
        layout[i].resize(dimensions.y);
        for (int j = 0; j < layout[i].size(); j++)
        {
            layout[i][j] = nullptr;
        }
    }
}

void City::set_name(std::string s)
{
    name = s;
}

std::string City::get_name()
{
    return name;
}

void City::set_balance(int i)
{
    balance = i;
}

int City::get_balance()
{
    return balance;
}

void City::set_population(int i)
{
    population = i;
}

void City::add_population(int i)
{
    population += i;
}

int City::get_population()
{
    return population;
}

void City::add_max_population(int i)
{
    max_population += i;
}

int City::get_max_population()
{
    return max_population;
}

int City::get_year()
{
    return year;
}

void City::increment_year()
{
    year++;
}

void City::set_dimensions(Dimensions d)
{
    dimensions = d;
}

Dimensions City::get_dimensions()
{
    return dimensions;
}

Grid& City::set_layout()
{
    return layout;
}

const Grid& City::get_layout()
{
    return layout;
}