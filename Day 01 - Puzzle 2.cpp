#include <algorithm>
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

	std::sort(calories.begin(), calories.end(), [](int a, int b) { return a > b; });
	int max3 = calories.at(0) + calories.at(1) + calories.at(2);

	std::cout << max3 << std::endl;

	return 0;
}
