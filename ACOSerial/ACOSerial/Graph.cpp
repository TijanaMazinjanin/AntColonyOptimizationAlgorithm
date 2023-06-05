#include "Graph.h"
using namespace std;

double get_distance(double city1_x, double city2_x, double city1_y, double city2_y) {
    //calculating Euclidean distance
    return sqrt(pow(city1_x - city2_x, 2) + pow(city1_y - city2_y, 2));
}

Graph::Graph(): size(0) {}

Graph::Graph(int size): size(size), matrix(size, vector<double>(size, 0)) {}

bool Graph::add_edge(int v1, int v2, double value) {
    if (v1 == v2) return false;

    matrix[v1][v2] = value;
    matrix[v2][v1] = value;
}

void Graph::initialize(double value) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            add_edge(i, j, value);
        }
    }
}

void Graph::initialize(vector<tuple<int, double, double>> city_coordinates) {
    for (int i = 0; i < size; i++) {
        for (int j = i+1; j < size; j++) {
            int distance = get_distance(get<1>(city_coordinates[i]), get<1>(city_coordinates[j]), 
                get<2>(city_coordinates[i]), get<2>(city_coordinates[j]));

            add_edge(i, j, distance);
        }
    }
}

void Graph:: multiply_matrix(double x) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] *= x;
        }
    }
}

void Graph:: print_matrix() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}