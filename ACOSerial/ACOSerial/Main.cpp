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
#define COLONY 100

#define ALPHA 1
#define BETA 5
#define EVAPORATION_RATE 0.5
#define INIT_PH 1


int main() {
	vector<tuple<int, double, double>> data;
	FileLoader file_loader;

	//file_loader.choose_file();
	file_loader.load(data);

	Graph distance_graph(data.size());
	distance_graph.initialize(data);
	
	srand(time(NULL));

	Algorithm algorithmSerial(NUM_OF_ITERATIONS, COLONY, ALPHA, BETA, EVAPORATION_RATE, INIT_PH, data);
	tick_count startTimeS = tick_count::now();
	algorithmSerial.runSerial();
	tick_count endTimeS = tick_count::now();
	cout << endl << "Serial time: " << (endTimeS - startTimeS).seconds() << endl << endl;

	Algorithm algorithmParallelTaskGroup(NUM_OF_ITERATIONS, COLONY, ALPHA, BETA, EVAPORATION_RATE, INIT_PH, data);
	tick_count startTimeTG = tick_count::now();
	algorithmParallelTaskGroup.runParallelTaskGroup();
	tick_count endTimeTG = tick_count::now();
	cout << endl << "Parallel time (task group): " << (endTimeTG - startTimeTG).seconds() << endl << endl;

	Algorithm algorithmParallelFor(NUM_OF_ITERATIONS, COLONY, ALPHA, BETA, EVAPORATION_RATE, INIT_PH, data);
	tick_count startTimeP = tick_count::now();
	algorithmParallelFor.runParallelFor();
	tick_count endTimeP = tick_count::now();
	cout << endl << "Parallel time (parallel_for): " << (endTimeP - startTimeP).seconds() << endl;
}