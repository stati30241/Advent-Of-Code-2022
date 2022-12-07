#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	int count = 0;
	for (std::string str = ""; std::getline(ifs, str); ) {
		// Replaces the seperators with spaces
		std::replace(str.begin(), str.end(), ',', ' ');
		std::replace(str.begin(), str.end(), '-', ' ');
		
		// Reads in the four values
		std::istringstream ss{ str };
		int a, b, c, d;
		ss >> a >> b >> c >> d;

		// Checks if one interval overlaps the other
		if ((a <= c && b >= c) || (c <= a && d >= a)) count++;
	}

	std::cout << count << std::endl;

	return 0;
}
