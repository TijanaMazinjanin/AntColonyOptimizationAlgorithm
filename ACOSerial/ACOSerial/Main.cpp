#pragma once
#include "FileLoader.h"
#include "Graph.h"
#include "Algorithm.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/tick_count.h"
using namespace tbb;
int main() {
	vector<tuple<int, double, double>> data;
	FileLoader file_loader;

	//file_loader.choose_file();
	file_loader.load(data);

	Graph distance_graph(data.size());
	distance_graph.initialize(data);
	
	srand(time(NULL));

	Algorithm algorithmSerial(100, 40, 1, 5, 0.5, 1, data);
	tick_count startTimeS = tick_count::now();
	algorithmSerial.runSerial();
	tick_count endTimeS = tick_count::now();
	cout << endl << "Serial time: " << (endTimeS - startTimeS).seconds() << endl << endl;

	Algorithm algorithm(100, 40, 1, 5, 0.5, 1, data);
	tick_count startTime = tick_count::now();
	algorithm.runParallel();
	tick_count endTime = tick_count::now();
	cout << endl << "Parallel time: " << (endTime - startTime).seconds() << endl;
}