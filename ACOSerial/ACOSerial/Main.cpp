#include "FileLoader.h"

int main() {
	vector<tuple<int, double, double>> data;
	FileLoader file_loader;

	file_loader.choose_file();
	file_loader.load(data);
	
}