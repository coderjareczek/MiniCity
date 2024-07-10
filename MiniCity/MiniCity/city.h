#pragma once
#include <string>
#include <vector>
#include <memory>
#include "road.h"
#include "residential_zone.h"
#include "industrial_zone.h"
#include "house.h"
#include "factory.h"
#include "school.h"
#include "hospital.h"

/**
 * @struct Dimensions
 * @brief Represents the dimensions of the city grid.
 */
struct Dimensions
{
    int x; ///< The width of the city grid.
    int y; ///< The height of the city grid.
};

typedef std::vector<std::vector<std::unique_ptr<Infrastructure>>> Grid;

/**
 * @class City
 * @brief Represents a city in the simulation.
 */
class City
{
    std::string name = "MiniCity"; ///< The name of the city.
    int balance = 20000; ///< The financial balance of the city.
    int population = 0; ///< The current population of the city.
    int max_population = 0; ///< The maximum population the city can support.
    int year = 2024; ///< The current year in the city simulation.
    Dimensions dimensions = { 10, 10 }; ///< The dimensions of the city grid.
    Grid layout; ///< The layout of the city, represented as a grid of infrastructures.

public:
    /**
     * @brief Constructs a new City object with default values.
     */
    City();

    /**
     * @brief Sets the name of the city.
     * @param s The new name of the city.
     */
    void set_name(std::string s);

    /**
     * @brief Gets the name of the city.
     * @return The name of the city.
     */
    std::string get_name();

    /**
     * @brief Sets the balance of the city.
     * @param i The new balance of the city.
     */
    void set_balance(int i);

    /**
     * @brief Gets the balance of the city.
     * @return The balance of the city.
     */
    int get_balance();

    /**
     * @brief Sets the population of the city.
     * @param i The new population of the city.
     */
    void set_population(int i);

    /**
     * @brief Adds to the current population of the city.
     * @param i The amount to add to the population.
     */
    void add_population(int i);

    /**
     * @brief Gets the current population of the city.
     * @return The current population of the city.
     */
    int get_population();

    /**
     * @brief Adds to the maximum population capacity of the city.
     * @param i The amount to add to the maximum population.
     */
    void add_max_population(int i);

    /**
     * @brief Gets the maximum population capacity of the city.
     * @return The maximum population capacity of the city.
     */
    int get_max_population();

    /**
     * @brief Gets the current year in the city simulation.
     * @return The current year.
     */
    int get_year();

    /**
     * @brief Increments the current year by one.
     */
    void increment_year();

    /**
     * @brief Sets the dimensions of the city grid.
     * @param d The new dimensions of the city grid.
     */
    void set_dimensions(Dimensions d);

    /**
     * @brief Gets the dimensions of the city grid.
     * @return The dimensions of the city grid.
     */
    Dimensions get_dimensions();

    /**
     * @brief Sets the layout of the city.
     * @return A reference to the layout grid of the city.
     */
    Grid& set_layout();

    /**
     * @brief Gets the layout of the city.
     * @return A const reference to the layout grid of the city.
     */
    const Grid& get_layout();
};