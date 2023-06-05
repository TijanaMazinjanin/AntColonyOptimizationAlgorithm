#pragma once
#include "FileLoader.h"
#include "Graph.h"
#include "Algorithm.h"
#include <stdlib.h>
#include <time.h>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/tick_count.h"

using namespace tbb;

#define NUM_OF_ITERATIONS 100
#define COLONY 40

#define ALPHA 1
#define BETA 5
#define EVAPORATION_RATE 0.5
#define INIT_PH 1


int main() {
	vector<tuple<int, double, double>> data;
	FileLoader file_loader;
	srand(time(NULL));

	file_loader.choose_file();
	file_loader.load(data);

	//initializing graph and filling it with data about cities
	Graph distance_graph(data.size());
	distance_graph.initialize(data);
	
	cout << endl;

	//SERIAL
	Algorithm algorithmSerial(NUM_OF_ITERATIONS, COLONY, ALPHA, BETA, EVAPORATION_RATE, INIT_PH, data);
	tick_count startTimeS = tick_count::now();
	algorithmSerial.runSerial();
	tick_count endTimeS = tick_count::now();
	cout << endl << "Serial time: " << (endTimeS - startTimeS).seconds() << endl << endl;

	//PARALLEL WITH TASK GROUP
	Algorithm algorithmParallelTaskGroup(NUM_OF_ITERATIONS, COLONY, ALPHA, BETA, EVAPORATION_RATE, INIT_PH, data);
	tick_count startTimeTG = tick_count::now();
	algorithmParallelTaskGroup.runParallelTaskGroup();
	tick_count endTimeTG = tick_count::now();
	cout << endl << "Parallel time (task group): " << (endTimeTG - startTimeTG).seconds() << endl << endl;

	//PARALLEL WITH PARALLEL_FOR
	Algorithm algorithmParallelFor(NUM_OF_ITERATIONS, COLONY, ALPHA, BETA, EVAPORATION_RATE, INIT_PH, data);
	tick_count startTimeP = tick_count::now();
	algorithmParallelFor.runParallelFor();
	tick_count endTimeP = tick_count::now();
	cout << endl << "Parallel time (parallel_for): " << (endTimeP - startTimeP).seconds() << endl;
}