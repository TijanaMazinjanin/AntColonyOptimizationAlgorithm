#include "ParallelColony.h"

void ParallelColony::operator()(const blocked_range<size_t> range) const
{
	for (int i = range.begin(); i != range.end(); ++i) {
		algorithm->choosePath(ants[i]);
	}
}
