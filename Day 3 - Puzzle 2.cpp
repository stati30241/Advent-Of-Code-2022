#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	int sum = 0;
	std::string sack1 = "", sack2 = "", sack3 = "";
	while (ifs >> sack1 >> sack2 >> sack3) {
		// Compares each char in the three rucksacks
		// I hate nested loops (this is very inefficient)
		for (size_t i = 0; i < sack1.size(); ++i) {
			for (size_t j = 0; j < sack2.size(); ++j) {
				for (size_t k = 0; k < sack3.size(); ++k) {
					if (sack1.at(i) == sack2.at(j) && sack2.at(j) == sack3.at(k)) {
						sum += std::isupper(sack1.at(i)) ? (sack1.at(i) - 64 + 26) : (sack1.at(i) - 96);
						goto break_out; // <-- Very evil never use (but if it works, it works)
					}
				}
			}
		}
	break_out:;
	}

	std::cout << sum << std::endl;

	return 0;
}
