#pragma once
#include "Ant.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "Algorithm.h"
using namespace tbb;
class ParallelColony {
public:
	Ant* ants;
	Algorithm* algorithm;
	void operator()(const blocked_range<size_t> range)const;
};