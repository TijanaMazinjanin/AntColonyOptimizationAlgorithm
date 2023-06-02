#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class FileLoader {
private:
	fstream file;
	string file_name;
public:
	FileLoader();
	void choose_file();
	void load(vector< tuple<int, double, double>>& data);
};