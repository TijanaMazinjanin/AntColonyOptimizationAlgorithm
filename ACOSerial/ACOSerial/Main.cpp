#pragma once
#include "FileLoader.h"
#include "Graph.h"
#include "Algorithm.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

int main() {
	vector<tuple<int, double, double>> data;
	FileLoader file_loader;

	//file_loader.choose_file();
	file_loader.load(data);

	Graph distance_graph(data.size());
	distance_graph.initialize(data);
	//distance_graph.print_matrix();
	srand(time(NULL));
	Algorithm algorithm(100, 50, 1, 5, 0.5, 1, data);
	algorithm.run();
}