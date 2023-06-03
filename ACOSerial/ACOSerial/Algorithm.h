#pragma once
#include "Graph.h"
#include "Ant.h"


using namespace std;

class Algorithm {
private:
	int iterations_number;
	int colony;
	int cities_number;
	double alpha;
	double beta;
	double evaporation_rate;
	double init_pheromone_value;

	Graph distance_graph;
	Graph pheromone_graph;
	vector<Ant> ants;
public:
	Algorithm(int iteration, int colony, double alpfa, double beta,
		double rho, double init_ph, vector<tuple<int, double, double>> city_coordinates);
	double getNumerator(int city1, int city2);
	double getDenominator(Ant ant, int current_city);
	double getProbability(Ant ant, int current_city, int destionation_city);
	int chooseCity(Ant ant);
	void choosePath(Ant &ant);
	void initializeAnts();
	void realeasePheromones(Ant &ant);
	void run();
};