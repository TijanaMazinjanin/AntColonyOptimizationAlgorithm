#include "Algorithm.h"

Algorithm::Algorithm(int iteration, int colony, double alpha, double beta, 
	double rho, double init_ph, vector<tuple<int, double, double>> city_coordinates):
	iterations_number(iteration), colony(colony), alpha(alpha), beta(beta),
	evaporation_rate(rho), init_pheromone_value(init_ph){

	distance_graph = Graph(city_coordinates.size());
	distance_graph.initialize(city_coordinates);

	pheromone_graph = Graph(city_coordinates.size());
	pheromone_graph.initialize(init_pheromone_value);
}

void Algorithm:: run() {

}