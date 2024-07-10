#include "view.h"

View::View()
{
	greeting();
	loop();
}

void View::loop()
{
	while (true)
	{
		print_name();
		show_menu(menu.get_main());
		char ch = _getch();
		if (switch_main(ch) == false)
			break;
	}
}

void View::show_menu(const std::vector<std::string>& menu)
{
    for (int i = 0; i < menu.size(); i++)
    {
        std::cout << i + 1 << ". " << menu[i] << " (Press " << i + 1 << ")" << std::endl;
    }
}

bool View::switch_main(char ch)
{
    switch (ch)
    {
    case '1':
        change_name();
        break;
    case '2':
        city_information();
        break;
    case '3':
        loop_infrastructure();
        break;
    case '4':
        goodbye();
        return false;
        break;
    }
    return true;
}

void View::greeting()
{
    Sleep(800);
    std::cout << "Welcome in MiniCity! It's time to start building your city!" << std::endl;
    Sleep(2300);
    std::cout << "Start by checking out \"City Information\"." << std::endl;
    Sleep(2200);
    press_space();
}

void View::press_space()
{
    std::cout << "(Press space to continue)" << std::endl;
    while (true)
    {
        char ch = _getch();
        if (ch == ' ')
        {
            break;
        }
    }
}

void View::print_name()
{
    system("cls");
    std::cout << city.get_name() << std::endl;
}

void View::change_name()
{
    std::cout << "Type new name for your city (don't use spaces): ";
    std::string tmp;
    std::cin >> tmp;
    city.set_name(tmp);
}

void View::city_information()
{
    system("cls");
    std::cout << "Balance: " << city.get_balance() << "$" << std::endl;
    std::cout << "Population: " << city.get_population() << std::endl;
    std::cout << "Max population: " << city.get_max_population() << std::endl;
    std::cout << "Size: " << city.get_dimensions().x << "x" << city.get_dimensions().y << std::endl;
    std::cout << "Year: " << city.get_year() << std::endl;
    print_city();

    std::cout << std::endl << "Go to the next year (Press 1)" << std::endl;
    std::cout << std::endl << "Exit to main menu (Press 2)" << std::endl;
    while (true)
    {
        char ch = _getch();
        if (ch == '1')
        {
            next_year();
            break;
        }
        else if (ch == '2')
        {
            return;
        }
    }
}

void View::print_city()
{
    std::cout << "This is your city:" << std::endl;
    for (int i = 0; i < city.get_dimensions().y; i++)
    {
        for (int j = 0; j < city.get_dimensions().x; j++)
        {
            if (city.get_layout()[j][i] == nullptr)
            {
                std::cout << "#";
            }
            else
            {
                std::cout << city.get_layout()[j][i]->get_symbol();
            }
        }
        std::cout << std::endl;
    }
}

void View::next_year()
{
    system("cls");
    std::cout << "Year " << city.get_year() << " is over!" << std::endl;
    city.increment_year();

    // Determine who works where and if you can pay maintenance cost
    int workers = city.get_population();

    if (Infrastructure::get_number_of('M') != 0)
    {
        int citizens_per_hospital = workers / Infrastructure::get_number_of('M');
        int hospital_workers = Infrastructure::get_number_of('M') * (citizens_per_hospital / 4);
        std::cout << " - " << hospital_workers << " citizens worked in hospitals" << std::endl;
        workers -= hospital_workers;

        int cost = Infrastructure::get_number_of('M') * 800;
        if (cost > city.get_balance())
        {
            city.set_balance(0);
            std::cout << "You didn't pay your bill for medical sector" << std::endl;
            city.add_population(-hospital_workers);
            std::cout << "People are leaving your city" << std::endl;
        }
        else
        {
            city.set_balance(city.get_balance() - cost);
            std::cout << " - " << "You paid " << cost << "$ for medical sector last year" << std::endl;
        }
    }

    if (Infrastructure::get_number_of('S') != 0)
    {
        int citizens_per_school = workers / Infrastructure::get_number_of('S');
        int school_workers = Infrastructure::get_number_of('S') * (citizens_per_school / 5);
        std::cout << " - " << school_workers << " citizens worked in schools" << std::endl;
        workers -= school_workers;

        int cost = Infrastructure::get_number_of('S') * 300;
        if (cost > city.get_balance())
        {
            city.set_balance(0);
            std::cout << "You didn't pay your education bill" << std::endl;
            city.add_population(-school_workers);
            std::cout << "People are leaving your city" << std::endl;
        }
        else
        {
            city.set_balance(city.get_balance() - cost);
            std::cout << " - " << "You paid " << cost << "$ for education last year" << std::endl;
        }
    }

    if (Infrastructure::get_number_of('F') != 0)
    {
        int factory_workers;
        if ((Infrastructure::get_number_of('F') * 4) >= workers)
            factory_workers = workers;
        else
            factory_workers = Infrastructure::get_number_of('F') * 4;

        std::cout << " - " << factory_workers << " citizens worked in factories" << std::endl;
        workers -= factory_workers;

        int earnings = factory_workers * 50;
        city.set_balance(city.get_balance() + earnings);
        std::cout << " - " << "Factories earned " << earnings << "$ for your city!" << std::endl;
    }

    if (workers == 0)
        std::cout << " - 0 citizens were employed" << std::endl;
    else
        std::cout << " - " << workers << " citizens were unemployed" << std::endl;

    // Calculate population increase
    Population_determinant_context context;
    Random random;
    int roll = random.rand_int(1, 6);
    if (roll == 1)
        context.set_determinant(std::make_unique<Population_determinant_tier_1>());
    else if (roll == 2 || roll == 3)
        context.set_determinant(std::make_unique<Population_determinant_tier_2>());
    else
        context.set_determinant(std::make_unique<Population_determinant_tier_3>());

    int natural_increase = context.execute_interest_finding(Infrastructure::get_number_of('S'), Infrastructure::get_number_of('M'));
    city.set_population(min(city.get_max_population(), (city.get_population() + natural_increase)));
    if (city.get_population() == 0)
    {
        std::cout << " - Your city is empty!" << std::endl;
    }
    else if (city.get_population() == city.get_max_population())
    {
        std::cout << " - Your city is full!" << std::endl;
    }
    else if (natural_increase > 0)
    {
        std::cout << std::endl << " - There are " << natural_increase << " new citizens" << std::endl;
        std::cout << "Welcome in " << city.get_name() << "!" << std::endl;
    }
    else
    {
        std::cout << " - There are no new citizens :(" << std::endl;
    }

    press_space();
}

void View::goodbye()
{
    system("cls");
    std::cout << "Thank you for playing MiniCity. See you next time!" << std::endl;
    Sleep(1200);
}

void View::loop_infrastructure()
{
    while (true)
    {
        print_name();
        show_menu(menu.get_infrastructure());
        char ch = _getch();
        if (switch_infrastructure(ch) == false)
            break;
    }
}

bool View::switch_infrastructure(char ch)
{
    switch (ch)
    {
    case '1':
        loop_roads();
        break;
    case '2':
        loop_zones();
        break;
    case '3':
        loop_buildings();
        break;
    case '4':
        return false;
        break;
    }
    return true;
}

void View::loop_roads() {
    while (true) {
        print_name();
        std::cout << "- Each tile of road (which is a 1x1 square) costs 100$." << std::endl;
        std::cout << "- You can only build one straight path at a time." << std::endl;
        std::cout << "- Maximum width of the road is 1." << std::endl;
        std::cout << "- You can only build on squares that are empty - '#'." << std::endl;
        show_menu(menu.get_road());
        char ch = _getch();
        if (switch_roads(ch) == false)
            break;
    }
}

bool View::switch_roads(char ch) {
    switch (ch) {
    case '1':
        build_road();
        break;
    case '2':
        return false;
        break;
    }
    return true;
}

void View::build_road() {
    print_name();
    print_city();
    std::cout << "For example top left corner tile would have coordinates x : 1 and y : 1," << std::endl;
    std::cout << "and bottom right corner tile would have coordinates x : 10 and y : 10." << std::endl;
    std::cout << "Enter coordinates for the starting tile of the new road." << std::endl;
    int starting_x;
    std::cout << "x = ";
    std::cin >> starting_x;
    int starting_y;
    std::cout << "y = ";
    std::cin >> starting_y;
    std::cout << "Enter coordinates for the last tile of the new road." << std::endl;
    int last_x;
    std::cout << "x = ";
    std::cin >> last_x;
    int last_y;
    std::cout << "y = ";
    std::cin >> last_y;

    if (starting_x != last_x && starting_y != last_y) {
        std::cout << "Construction unsuccessful - road wasn't a straight path of width 1" << std::endl;
        press_space();
        return;
    }

    int price;
    if (starting_x == last_x) {
        price = 100 * (abs(last_y - starting_y) + 1);
    }
    else {
        price = 100 * (abs(last_x - starting_x) + 1);
    }

    if (city.get_balance() < price) {
        std::cout << "Construction unsuccessful - not enough money" << std::endl;
        press_space();
        return;
    }

    if (starting_x < 1 || starting_x > city.get_dimensions().x || starting_y < 1 || starting_y > city.get_dimensions().y) {
        std::cout << "Construction unsuccessful - you can't build outside of the city" << std::endl;
        press_space();
        return;
    }

    // Check if tiles are empty - '#'
    if (starting_x > last_x) {
        std::swap(starting_x, last_x);
    }
    if (starting_y > last_y) {
        std::swap(starting_y, last_y);
    }
    for (int i = starting_x - 1; i < last_x; i++) {
        for (int j = starting_y - 1; j < last_y; j++) {
            if (city.get_layout()[i][j] != nullptr) {
                std::cout << "Construction unsuccessful - you can only build on empty spaces" << std::endl;
                press_space();
                return;
            }
        }
    }

    // All conditions met, constructing road
    city.set_balance(city.get_balance() - price);

    for (int i = starting_x - 1; i < last_x; i++) {
        for (int j = starting_y - 1; j < last_y; j++) {
            city.set_layout()[i][j] = std::make_unique<Road>();
        }
    }

    print_name();
    std::cout << "Construction successful!" << std::endl;
    print_city();
    press_space();
}

void View::loop_zones()
{
	while (true)
	{
		print_name();
		std::cout << "- Each tile of a zone (which is a 1x1 square) costs 20$." << std::endl;
		std::cout << "- You can only chart rectangular zones" << std::endl;
		std::cout << "- You can only chart on squares that are empty - '#'." << std::endl;
		show_menu(menu.get_zone());
		char ch = _getch();
		if (switch_zone(ch) == false)
			break;
	}
}

bool View::switch_zone(char ch)
{
	switch (ch)
	{
	case '1':
		build_zone<Residential_zone>();
		break;
	case '2':
		build_zone<Industrial_zone>();
		break;
	case '3':
		return false;
		break;
	}
	return true;
}

template <typename T>
void View::build_zone()
{
	print_name();
	print_city();
	std::cout << "For example top left corner tile would have coordinates x : 1 and y : 1," << std::endl;
	std::cout << "and bottom right corner tile would have coordinates x : 10 and y : 10." << std::endl;
	std::cout << "Enter coordinates for the corner tile of the zone." << std::endl;
	int starting_x;
	std::cout << "x = ";
	std::cin >> starting_x;
	int starting_y;
	std::cout << "y = ";
	std::cin >> starting_y;
	std::cout << "Enter coordinates for the opposite tile of the zone." << std::endl;
	int last_x;
	std::cout << "x = ";
	std::cin >> last_x;
	int last_y;
	std::cout << "y = ";
	std::cin >> last_y;

	int x_diff = abs(starting_x - last_x) + 1;
	int y_diff = abs(starting_y - last_y) + 1;
	int price = x_diff * y_diff * 20;


	if (city.get_balance() < price)
	{
		std::cout << "Charting unsuccessful - not enough money" << std::endl;
		press_space();
		return;
	}

	if (starting_x < 1 or starting_x > city.get_dimensions().x or starting_y < 1 or starting_y > city.get_dimensions().y)
	{
		std::cout << "Charting unsuccessful - you can't build outside of the city" << std::endl;
		press_space();
		return;
	}

	//Check if tiles are empty - '#'
	if (starting_x > last_x)
	{
		std::swap(starting_x, last_x);
	}
	if (starting_y > last_y)
	{
		std::swap(starting_y, last_y);
	}
	for (int i = starting_x - 1; i < last_x; i++)
	{
		for (int j = starting_y - 1; j < last_y; j++)
		{
			if (city.get_layout()[i][j] != nullptr)
			{
				std::cout << "Charting unsuccessful - you can only chart on empty spaces" << std::endl;
				press_space();
				return;
			}
		}
	}

	// All conditions met, charting successful
	city.set_balance(city.get_balance() - price);

	for (int i = starting_x - 1; i < last_x; i++)
	{
		for (int j = starting_y - 1; j < last_y; j++)
		{
			city.set_layout()[i][j] = std::make_unique<T>();
		}
	}



	print_name();
	std::cout << "Construction successful!" << std::endl;
	print_city();
	press_space();
}

/* ------------------------------ Buildings ------------------------------ */

void View::loop_buildings()
{
	while (true)
	{
		print_name();
		std::cout << "- Each building has a different price" << std::endl;
		std::cout << "- You can only build them in specific zones" << std::endl;
		show_menu(menu.get_building());
		char ch = _getch();
		if (switch_building(ch) == false)
			break;
	}
}

bool View::switch_building(char ch)
{
	switch (ch)
	{
	case '1':
		build_house();
		break;
	case '2':
		build_factory();
		break;
	case '3':
		loop_special_buildings();
		break;
	case '4':
		return false;
		break;
	}
	return true;
}

void View::build_house()
{
	print_name();
	std::cout << "House costs 100$" << std::endl;
	std::cout << "You can only build it on empty residential zone tiles - 'r'" << std::endl;
	std::cout << "Bulding a house increases your population by 2" << std::endl;
	print_city();
	std::cout << "For example top left corner tile would have coordinates x : 1 and y : 1," << std::endl;
	std::cout << "and bottom right corner tile would have coordinates x : 10 and y : 10." << std::endl;
	std::cout << "Enter coordinates for the house." << std::endl;
	int x;
	std::cout << "x = ";
	std::cin >> x;
	int y;
	std::cout << "y = ";
	std::cin >> y;

	int price = 100;

	if (city.get_balance() < price)
	{
		std::cout << "Construction unsuccessful - not enough money" << std::endl;
		press_space();
		return;
	}
	if (x < 1 or x > city.get_dimensions().x or y < 1 or y > city.get_dimensions().y)
	{
		std::cout << "Constrution unsuccessful - you can't build outside of the city" << std::endl;
		press_space();
		return;
	}

	//Check if tiles are residential zone tiles - 'r'
	if (city.get_layout()[x - 1][y - 1] == nullptr or city.get_layout()[x - 1][y - 1]->get_symbol() != 'r')
	{
		std::cout << "Constrution unsuccessful - you can only build on residential zone tiles - 'r'" << std::endl;
		press_space();
		return;
	}

	//All conditions met, construction successful
	city.set_balance(city.get_balance() - price);

	city.set_layout()[x - 1][y - 1] = std::make_unique<House>();
	city.add_population(2);
	city.add_max_population(4);

	print_name();
	std::cout << "Construction successful!" << std::endl;
	print_city();
	press_space();
}

void View::build_factory()
{
	print_name();
	std::cout << "Factory costs 500$" << std::endl;
	std::cout << "You can only build it on empty industrial zone tiles - 'i'" << std::endl;
	std::cout << "A factory earns you money for every citizen who works there - max 4" << std::endl;
	print_city();
	std::cout << "For example top left corner tile would have coordinates x : 1 and y : 1," << std::endl;
	std::cout << "and bottom right corner tile would have coordinates x : 10 and y : 10." << std::endl;
	std::cout << "Enter coordinates for the factory." << std::endl;
	int x;
	std::cout << "x = ";
	std::cin >> x;
	int y;
	std::cout << "y = ";
	std::cin >> y;

	int price = 500;


	if (city.get_balance() < price)
	{
		std::cout << "Construction unsuccessful - not enough money" << std::endl;
		press_space();
		return;
	}

	if (x < 1 or x > city.get_dimensions().x or y < 1 or y > city.get_dimensions().y)
	{
		std::cout << "Constrution unsuccessful - you can't build outside of the city" << std::endl;
		press_space();
		return;
	}

	//Check if tiles are industrial zone tiles - 'i'
	if (city.get_layout()[x - 1][y - 1] == nullptr or city.get_layout()[x - 1][y - 1]->get_symbol() != 'i')
	{
		std::cout << "Constrution unsuccessful - you can only build on industrial zone tiles - 'i'" << std::endl;
		press_space();
		return;
	}

	// All conditions met, construction successful
	city.set_balance(city.get_balance() - price);
	city.set_layout()[x - 1][y - 1] = std::make_unique<Factory>();


	print_name();
	std::cout << "Construction successful!" << std::endl;
	print_city();
	press_space();
}

void View::loop_special_buildings()
{
	while (true)
	{
		print_name();
		std::cout << "- You have to meet particular criteria to build special buildings" << std::endl;
		std::cout << "- Special buildings will attract people to your city" << std::endl;
		std::cout << "- Special buildings have maintenance cost that you have to pay every year" << std::endl;
		std::cout << "- If you don't have sufficient balance at the end of the year people will start leaving you city" << std::endl;
		show_menu(menu.get_special_building());
		char ch = _getch();
		if (switch_special_building(ch) == false)
			break;
	}
}

bool View::switch_special_building(char ch)
{
	switch (ch)
	{
	case '1':
		build_school();
		break;
	case '2':
		build_hospital();
		break;
	case '3':
		return false;
		break;
	}
	return true;
}

void View::build_school()
{
	print_name();
	std::cout << "School costs 1000$" << std::endl;
	std::cout << "You can only build it on empty residential zone tiles - 'r'" << std::endl;
	std::cout << "You have to have at least 5 houses for every school" << std::endl;
	std::cout << "Make sure to have 300$ at the end of the year as it is its annual maintenance cost" << std::endl;
	print_city();
	std::cout << "For example top left corner tile would have coordinates x : 1 and y : 1," << std::endl;
	std::cout << "and bottom right corner tile would have coordinates x : 10 and y : 10." << std::endl;
	std::cout << "Enter coordinates for the school." << std::endl;
	int x;
	std::cout << "x = ";
	std::cin >> x;
	int y;
	std::cout << "y = ";
	std::cin >> y;

	int price = 1000;

	if (city.get_balance() < price)
	{
		std::cout << "Construction unsuccessful - not enough money" << std::endl;
		press_space();
		return;
	}
	if (x < 1 or x > city.get_dimensions().x or y < 1 or y > city.get_dimensions().y)
	{
		std::cout << "Constrution unsuccessful - you can't build outside of the city" << std::endl;
		press_space();
		return;
	}

	// Check if tiles are residential zone tiles - 'r'
	if (city.get_layout()[x - 1][y - 1] == nullptr or city.get_layout()[x - 1][y - 1]->get_symbol() != 'r')
	{
		std::cout << "Constrution unsuccessful - you can only chart on residential zone tiles - 'r'" << std::endl;
		press_space();
		return;
	}

	// Check if there are at least 5 houses per school
	if ((Infrastructure::get_number_of('H') / (Infrastructure::get_number_of('S') + 1)) < 5)
	{
		std::cout << "Constrution unsuccessful - you need at least 5 houses per school" << std::endl;
		press_space();
		return;
	}

	// All conditions met, construction successful
	city.set_balance(city.get_balance() - price);

	city.set_layout()[x - 1][y - 1] = std::make_unique<School>();

	print_name();
	std::cout << "Construction successful!" << std::endl;
	print_city();
	press_space();
}

void View::build_hospital()
{
	print_name();
	std::cout << "Hospital costs 2000$" << std::endl;
	std::cout << "You can only build it on empty residential zone tiles - 'r'" << std::endl;
	std::cout << "It is denoted as 'M' for Medical Facility" << std::endl;
	std::cout << "You have to have at least 1 school for every hospital" << std::endl;
	std::cout << "Make sure to have 600$ at the end of the year as it is its annual maintenance cost" << std::endl;
	print_city();
	std::cout << "For example top left corner tile would have coordinates x : 1 and y : 1," << std::endl;
	std::cout << "and bottom right corner tile would have coordinates x : 10 and y : 10." << std::endl;
	std::cout << "Enter coordinates for the school." << std::endl;
	int x;
	std::cout << "x = ";
	std::cin >> x;
	int y;
	std::cout << "y = ";
	std::cin >> y;

	int price = 2000;

	if (city.get_balance() < price)
	{
		std::cout << "Construction unsuccessful - not enough money" << std::endl;
		press_space();
		return;
	}
	if (x < 1 or x > city.get_dimensions().x or y < 1 or y > city.get_dimensions().y)
	{
		std::cout << "Constrution unsuccessful - you can't build outside of the city" << std::endl;
		press_space();
		return;
	}

	// Check if tiles are residential zone tiles - 'r'
	if (city.get_layout()[x - 1][y - 1] == nullptr or city.get_layout()[x - 1][y - 1]->get_symbol() != 'r')
	{
		std::cout << "Constrution unsuccessful - you can only build on residential zone tiles - 'r'" << std::endl;
		press_space();
		return;
	}

	// Check if there is 1 school per hospital
	if (Infrastructure::get_number_of('S') < (Infrastructure::get_number_of('M') + 1))
	{
		std::cout << "Constrution unsuccessful - you need at least 1 school per hospital" << std::endl;
		press_space();
		return;
	}

	// All conditions met, construction successful
	city.set_balance(city.get_balance() - price);

	city.set_layout()[x - 1][y - 1] = std::make_unique<Hospital>();

	print_name();
	std::cout << "Construction successful!" << std::endl;
	print_city();
	press_space();
}