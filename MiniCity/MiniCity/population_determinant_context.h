#pragma once

#include <memory>
#include "population_determinant.h"

class Population_determinant_context
{ 
    std::unique_ptr<Population_determinant> strategy;
public:
    void set_determinant(std::unique_ptr<Population_determinant> &&strategy_)
    {
        strategy = std::move(strategy_);
    }

    int execute_interest_finding(const int schools, const int hospitals) const
    {
        return strategy->find_interest(schools, hospitals);
    }
};