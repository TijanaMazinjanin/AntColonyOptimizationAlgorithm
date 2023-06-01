#include "FileLoader.h"
#include "Graph.h"

int main() {
	vector<tuple<int, double, double>> data;
	FileLoader file_loader;

	file_loader.choose_file();
	file_loader.load(data);

	Graph distance_graph = Graph(data.size());
	distance_graph.initialize(data);
	distance_graph.print_matrix();
	
}