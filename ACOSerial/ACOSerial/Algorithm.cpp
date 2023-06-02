#include "Algorithm.h"

Algorithm::Algorithm(int iteration, int colony, double alpha, double beta, 
	double rho, double init_ph, vector<tuple<int, double, double>> city_coordinates):
	iterations_number(iteration), colony(colony), alpha(alpha), beta(beta),
	evaporation_rate(rho), init_pheromone_value(init_ph), ants(colony, Ant(city_coordinates.size())), cities_number(city_coordinates.size()){

	distance_graph = Graph(cities_number);
	distance_graph.initialize(city_coordinates);

	pheromone_graph = Graph(cities_number);
	pheromone_graph.initialize(init_pheromone_value);
}

double Algorithm::getNumerator(int city1, int city2)
{
	return pow(pheromone_graph.matrix[city1][city2], alpha) * pow((1 / distance_graph.matrix[city1][city2]), beta);

}

double Algorithm::getDenominator(Ant ant, int current_city)
{
	double denominator = 0;
	for (int i = 0; i < ant.cities.size(); i++) {
		if (ant.cities[i] == 0) {
			denominator += getNumerator(current_city, i);
		}
	}
	return denominator;
}

double Algorithm::getProbability(Ant ant, int current_city, int destionation_city)
{
	return getNumerator(current_city, destionation_city) / getDenominator(ant, current_city);
}
static bool sortbysec(const tuple<int, double>& a,
	const tuple<int, double>& b)
{
	return (get<1>(a) < get<1>(b));
}

int Algorithm::chooseCity(Ant ant)
{
	vector<tuple<int, double>> probabilities;
	int current_city = ant.getCurrentCity();
	for (int i = 0; i < ant.cities.size(); i++) {
		if (ant.cities[i] == 0) {
			probabilities.push_back(make_tuple(i, getProbability(ant, current_city, i)));
		}
	}
	sort(probabilities.begin(), probabilities.end(), sortbysec);

	double random_num = (double) rand() / RAND_MAX;

	for (int i = 0; i < probabilities.size(); i++) {
		if (i > 0) {
			get<1>(probabilities[i]) += get<1>(probabilities[i - 1]);
		}
		if (random_num <= get<1>(probabilities[i])) {
			return get<0>(probabilities[i]);
		}
	}
	return get<0>(probabilities[probabilities.size() - 1]);
}

void Algorithm::choosePath(Ant &ant)
{
	while (ant.found_cities_number != ant.cities.size()-1) {
		int last_city = ant.getCurrentCity();
		int new_city = chooseCity(ant);
		int path_len = distance_graph.matrix[last_city][new_city];
		ant.total_distance += path_len;
		ant.addCity(new_city);
	}
	int last_city = ant.getCurrentCity();
	int first_city = ant.cities_order[0];
	int path_len = distance_graph.matrix[last_city][first_city];
	ant.total_distance += path_len;
}

void Algorithm::initializeAnts()
{
	for(Ant ant : ants) {
		ant.setDefault(cities_number);
	}
}

void Algorithm:: run() {
	initializeAnts();
	for(Ant ant : ants){
		choosePath(ant);
		ant.printPath();
	}
}
