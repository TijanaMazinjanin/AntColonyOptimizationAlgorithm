#pragma once
#include <vector>
#include <iostream>
#include<algorithm>
using namespace std;

struct Ant {
	int total_distance;
	int found_cities_number;
	vector<int> cities;
	vector<int> cities_order;

	Ant(int cities_num);
	void addFirst(int cities_num);
	void addCity(int city);
	int getCurrentCity();
	void setDefault(int cities_num);
	void printPath();
};