#include <iostream>
#include <fstream>
#include <string>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	int cycle = 0;
	int regX = 1;
	std::string crtScreen(40 * 6, '.');

	// Goes through each token seperated by a space
	// This works because noop in only one instruction
	// and it only takes one cycle, while addx is two
	// instruction and it takes two cycles
	std::string token = "";
	while (ifs >> token) {
		cycle++;

		// Easier than checking if its an integer
		if (token != "noop" && token != "addx") {
			regX += std::stoi(token);
		}

		// Updates the crt screen
		int x = cycle % 40;
		if (regX - 1 <= x && regX + 1 >= x) {
			crtScreen.at(cycle - 1) = 'x';
		}
	}

	// Prints the crt screen
	for (size_t i = 0; i < 6; ++i) {
		for (size_t j = 0; j < 40; ++j) {
			std::cout << crtScreen.at(i * 40 + j);
		}
		std::cout << std::endl;
	}

	return 0;
}
