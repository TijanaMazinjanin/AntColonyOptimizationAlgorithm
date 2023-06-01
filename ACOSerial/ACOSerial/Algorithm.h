#include "Graph.h"

using namespace std;

class Algorithm {
private:
	int iterations_number;
	int colony;
	double alpha;
	double beta;
	double evaporation_rate;
	double init_pheromone_value;

	Graph distance_graph;
	Graph pheromone_graph;
public:
	Algorithm(int iteration, int colony, double alpfa, double beta,
		double rho, double init_ph, vector<tuple<int, double, double>> city_coordinates);

	void run();
};