#include "Algorithm.h"
#include "ParallelColony.h"


Algorithm::Algorithm(int iteration, int colony, double alpha, double beta, 
	double rho, double init_ph, vector<tuple<int, double, double>> city_coordinates):

	iterations_number(iteration), colony(colony), alpha(alpha), beta(beta),
	evaporation_rate(rho), init_pheromone_value(init_ph), grain_size(colony/16),
	ants(colony, Ant(city_coordinates.size())), cities_number(city_coordinates.size()){

	distance_graph = Graph(cities_number);
	distance_graph.initialize(city_coordinates);

	pheromone_graph = Graph(cities_number);
	pheromone_graph.initialize(init_pheromone_value);
}

double Algorithm::getNumerator(int city1, int city2)
{
	return pow(pheromone_graph.matrix[city1][city2], alpha) * pow((1 / distance_graph.matrix[city1][city2]), beta);
}

double Algorithm::getDenominator(Ant& ant, int current_city)
{
	double denominator = 0;
	for (int i = 0; i < ant.cities.size(); i++) {
		if (ant.cities[i] == 0) {
			denominator += getNumerator(current_city, i);
		}
	}
	return denominator;
}

double Algorithm::getProbability(Ant& ant, int current_city, int destionation_city)
{
	return getNumerator(current_city, destionation_city) / getDenominator(ant, current_city);
}
static bool sortbysec(const tuple<int, double>& a, const tuple<int, double>& b)
{//function used for sorting a structure by second element of tuple
	return (get<1>(a) < get<1>(b));
}

int Algorithm::chooseCity(Ant& ant)
{
	vector<tuple<int, double>> probabilities;
	int current_city = ant.getCurrentCity();
	for (int i = 0; i < ant.cities.size(); i++) {
		if (ant.cities[i] == 0) {
			probabilities.push_back(make_tuple(i, getProbability(ant, current_city, i)));
		}
	}
	sort(probabilities.begin(), probabilities.end(), sortbysec);

	//generating a random number between 0 and 1
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
	//adding distance from last city to the first
	int last_city = ant.getCurrentCity();
	int first_city = ant.cities_order[0];
	int path_len = distance_graph.matrix[last_city][first_city];
	ant.total_distance += path_len;
}

void Algorithm:: realeasePheromones(Ant &ant) {
	for (int i = 0; i < ant.cities_order.size() - 1; i++) {
		int j = i + 1;

		int city1 = ant.cities_order[i];
		int city2 = ant.cities_order[j];

		pheromone_graph.matrix[city1][city2] += 1 / ant.total_distance;
		pheromone_graph.matrix[city2][city1] += 1 / ant.total_distance;
	}

	int city1 = ant.cities_order[0];
	int city2 = ant.cities_order.back();
	 
	pheromone_graph.matrix[city1][city2] += 1 / (double)ant.total_distance;
	pheromone_graph.matrix[city2][city1] += 1 / (double)ant.total_distance;
}

void Algorithm::initializeAnts()
{
	for(Ant &ant : ants) {
		ant.setDefault(cities_number);
	}
}

void Algorithm::runParallelChosePath(int ant1, int ant2) {
	if ((grain_size == 0) || (ant2 - ant1 <= grain_size)) {
		choosePathForAnts(ant1, ant2);
	}
	else {
		task_group t;
		t.run([&] {runParallelChosePath(ant1, ant1 + (ant2 - ant1) / 2); });
		t.run([&] {runParallelChosePath(ant1 + (ant2 - ant1) / 2, ant2); });
		t.wait();
	}
}

void Algorithm::runSerial() {
	for (int i = 0; i < iterations_number; i++) {
		initializeAnts();

		choosePathForAnts(0, colony);

		updatePheromones();
	}
	calculateMinimalDistance();
}

void Algorithm::runParallelTaskGroup()
{
	for (int i = 0; i < iterations_number; i++) {
		initializeAnts();

		runParallelChosePath(0, colony);

		updatePheromones();
	}

	calculateMinimalDistance();
}

void Algorithm::runParallelFor() {
	for (int i = 0; i < iterations_number; i++) {
		initializeAnts();

		ParallelColony parallelColony;
		parallelColony.algorithm = this;
		parallelColony.ants = &ants[0];
		parallel_for(blocked_range<size_t>(0, colony), parallelColony, auto_partitioner());
		
		updatePheromones();
	}

	calculateMinimalDistance();
}

void Algorithm:: choosePathForAnts(int ant1, int ant2) {
	for (int i = ant1; i < ant2; i++) {
		Ant& ant = ants[i];
		choosePath(ant);
	}
}

void Algorithm:: updatePheromones() {
	pheromone_graph.multiply_matrix(1 - evaporation_rate);
	for (Ant& ant : ants) {
		realeasePheromones(ant);
	}
}

void Algorithm::calculateMinimalDistance()
{
	double minimalt_distance = numeric_limits<double>::infinity();
	Ant* minimalt_ant = &ants[0];

	for (Ant& ant : ants) {
		if (ant.total_distance < minimalt_distance) {
			minimalt_ant = &ant;
			minimalt_distance = ant.total_distance;
		}
	}

	cout << "Minimal distance is: " << minimalt_distance << endl;
	cout << "Citites order:  ";
	minimalt_ant->printPath();
}
