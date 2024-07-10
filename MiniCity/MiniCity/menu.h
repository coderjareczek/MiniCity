#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> Options;

class Menu
{
	Options main = { "Change Name", "City Information", "Infrastructure", "Exit" };
	Options infrastructure = { "Roads", "Zones", "Buildings", "Go Back"};
	Options road = { "Build Road", "Go Back" };
	Options zone = { "Chart Residential Zone", "Chart Industrial Zone","Go Back" };
	Options building = { "Build a House", "Build a Factory", "Build a Special Building", "Go Back"};
	Options special_building = {"School", "Hospital", "Go Back"};
public:
	Options get_main()
	{
		return main;
	}

	Options get_infrastructure()
	{
		return infrastructure;
	}

	Options get_road()
	{
		return road;
	}

	Options get_zone()
	{
		return zone;
	}

	Options get_building()
	{
		return building;
	}

	Options get_special_building()
	{
		return special_building;
	}
};