#pragma once

#include <map>

class Population_determinant
{
public:
    virtual ~Population_determinant() = default;
    virtual int find_interest(const int schools, const int hospitals) const = 0;
};