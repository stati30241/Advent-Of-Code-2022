#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::ifstream ifs{ "input.txt " };
	if (!ifs.is_open()) return -1;
	
	std::vector<int> calories = { 0 };
	for (std::string str = ""; std::getline(ifs, str); ) {
		if (str == "") calories.push_back(0);
		else {
			int cal = std::stoi(str);
			calories.back() += cal;
		}
	}

	int max = 0; // I'm assuming you can only have a positive number of calories
	for (int cal : calories) {
		if (cal > max) max = cal;
	}

	std::cout << max << std::endl;

	return 0;
}
