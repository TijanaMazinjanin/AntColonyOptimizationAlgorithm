#pragma once
#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

struct Graph{
	vector<vector<double>> matrix;
	int size;
	Graph();
	Graph(int size);
	bool add_edge(int v1, int v2, double value);
	void initialize(double value);
	void initialize(vector<tuple<int, double, double>>);
	void multiply_matrix(double x);
	void print_matrix();
};