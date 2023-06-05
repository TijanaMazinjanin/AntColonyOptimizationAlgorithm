#include "FileLoader.h"

using namespace std;

FileLoader::FileLoader() {
	file_name = "";
	file.open(file_name, fstream::in);
}

void FileLoader::choose_file() {
	while (true) {
		cout << "\nEnter input file name: " << endl;
		cin >> this->file_name;

		file.open(this->file_name, fstream::in);
		if (file.is_open()) {
			break;
		}
		else {
			cout << "\n\tERROR: wrong input file name!" << endl;
			cout << "\tTry again" << endl;
			continue;
		}
	}
}

void FileLoader::load(vector<tuple<int, double, double>>& data) {
	while (!file.eof()) {
		int city_number;
		double x;
		double y;

		file >> city_number;
		file >> x;
		file >> y;

		data.push_back(make_tuple(city_number, x, y));
	}
}