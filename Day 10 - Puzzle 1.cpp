#include <iostream>
#include <fstream>
#include <string>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	int cycle = 0;
	int regX = 1;
	int sum = 0;

	// Goes through each token seperated by a space
	// This works because noop in only one instruction
	// and it only takes one cycle, while addx is two
	// instruction and it takes two cycles
	std::string token = "";
	while (ifs >> token) {
		cycle++;

		if ((cycle - 20) % 40 == 0) sum += regX * cycle;

		// Easier than checking if its an integer
		if (token != "noop" && token != "addx") {
			regX += std::stoi(token);
		}
	}

	std::cout << sum << std::endl;

	return 0;
}
