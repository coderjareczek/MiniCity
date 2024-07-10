#pragma once
#include <iostream>
#include <windows.h>
#include <cmath>
#include <utility>
#include <memory>
#include <algorithm>
#include "conio.h"
#include "city.h"
#include "menu.h"
#include "population_determinant_context.h"
#include "population_determinant_tiers.h"
#include "random.h"


/**
 * @brief The View class manages the user interface and interaction for managing city infrastructure.
 */
class View
{
	City city;
	Menu menu;

public:
	/**
	* @brief Displays greeting and calls loop.
	*/
	View();

	/**
	* @brief Loops through main menu.
	*/
	void loop();

	/**
	 * @brief Displays the menu options.
	 *
	 * @param menu A vector of strings representing the menu options.
	 */
	void show_menu(const std::vector<std::string>& menu);

	/**
	 * @brief Handles the main menu switch-case logic.
	 *
	 * @param ch The character input for the menu selection.
	 * @return true if the menu loop should continue, false if it should exit.
	 */
	bool switch_main(char ch);

	/**
	 * @brief Displays the greeting message at the start of the program.
	 */
	void greeting();

	/**
	 * @brief Waits for the user to press the spacebar to continue.
	 */
	void press_space();

	/**
	 * @brief Clears the screen and prints the city's name.
	 */
	void print_name();

	/**
	 * @brief Changes the name of the city based on user input.
	 */
	void change_name();


	/* ------------------------------ City Information ------------------------------ */

	/**
	 * @brief Displays the city information.
	 */
	void city_information();

	/**
	 * @brief Prints the layout of the city.
	 */
	void print_city();

	/**
	 * @brief Advances the city by one year and performs necessary updates.
	 */
	void next_year();

	/**
	 * @brief Displays the goodbye message.
	 */
	void goodbye();

	/* ------------------------------ Infrastructure ------------------------------ */

	/**
	 * @brief Starts the infrastructure loop.
	 */
	void loop_infrastructure();

	/**
	 * @brief Handles the infrastructure menu options.
	 * @param ch The character input representing the menu option.
	 * @return True if the loop should continue, false otherwise.
	 */
	bool switch_infrastructure(char ch);

	/* ------------------------------ Roads ------------------------------ */

	/**
	 * @brief Main loop for managing road construction.
	 */
	void loop_roads();

	/**
	 * @brief Handles the road construction based on user input.
	 * @param ch Character input for menu selection.
	 * @return False if the user chooses to exit, true otherwise.
	 */
	bool switch_roads(char ch);

	/**
	 * @brief Initiates the road construction process.
	 */
	void build_road();

	/* ------------------------------ Zones ------------------------------ */

    /**
        * @brief Initializes a loop for building zones in the city.
        *
        * This function displays instructions and allows the user to build rectangular zones.
        */
    void loop_zones();

    /**
        * @brief Switches between different types of zones based on user input.
        *
        * @param ch The character representing the user's choice.
        * @return true if the loop should continue, false if it should break.
        */
    bool switch_zone(char ch);

    /**
        * @brief Builds a rectangular zone of a specified type (Residential or Industrial).
        *
        * This templated function prompts the user for coordinates and validates the build conditions.
        * @tparam T Type of zone to build (Residential_zone or Industrial_zone).
        */
    template <typename T>
    void build_zone();

    /**
        * @brief Initializes a loop for building different types of buildings in the city.
        *
        * This function displays instructions and allows the user to select and build various types of buildings.
        */
    void loop_buildings();

    /**
        * @brief Switches between different types of buildings based on user input.
        *
        * @param ch The character representing the user's choice.
        * @return true if the loop should continue, false if it should break.
        */
    bool switch_building(char ch);

    /**
        * @brief Builds a residential house in the city.
        *
        * This function prompts the user for coordinates and validates the build conditions before
        * constructing a house.
        */
    void build_house();

    /**
        * @brief Builds an industrial factory in the city.
        *
        * This function prompts the user for coordinates and validates the build conditions before
        * constructing a factory.
        */
    void build_factory();

    /**
        * @brief Initializes a loop for building special buildings in the city.
        *
        * This function displays instructions and allows the user to select and build special buildings.
        */
    void loop_special_buildings();

    /**
        * @brief Switches between different types of special buildings based on user input.
        *
        * @param ch The character representing the user's choice.
        * @return true if the loop should continue, false if it should break.
        */
    bool switch_special_building(char ch);

    /**
        * @brief Builds a school in the city.
        *
        * This function prompts the user for coordinates and validates the build conditions before
        * constructing a school.
        */
    void build_school();

    /**
        * @brief Builds a hospital in the city.
        *
        * This function prompts the user for coordinates and validates the build conditions before
        * constructing a hospital.
        */
    void build_hospital();
};