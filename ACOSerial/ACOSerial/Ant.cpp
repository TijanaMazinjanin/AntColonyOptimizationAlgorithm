#include "Ant.h"

Ant::Ant(int cities_num):total_distance(0), cities(cities_num , 0), cities_order(cities_num , 0), found_cities_number(-1)
{
	addFirst(cities_num);
}

void Ant::addFirst(int cities_num)
{
	int random_city = rand() % cities_num;
	addCity(random_city);
}

void Ant::addCity(int city)
{
	found_cities_number++;
	cities[city] = 1;
	cities_order[found_cities_number] = city;
}

int Ant::getCurrentCity()
{
	return cities_order[found_cities_number];
}

void Ant::setDefault(int cities_num)
{
	total_distance = 0;
	found_cities_number = -1;
	for (int i = 0; i < cities.size(); i++)
	{
		cities[i] = 0;
	}
	for (int i = 0; i < cities_order.size(); i++)
	{
		cities_order[i] = 0;
	}
	addFirst(cities_num);
}

void Ant::printPath()
{
	for (int i = 0; i < cities_order.size(); i++)
		cout << cities_order.at(i) << ' ';
	cout << endl;
}
