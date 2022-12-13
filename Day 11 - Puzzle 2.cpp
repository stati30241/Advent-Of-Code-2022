#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


// Monkey structure to keep track of monkeys
struct Monkey {
	std::vector<unsigned long long> items;
	char operation;
	int operationAmount;
	unsigned long long test;
	size_t throwTrue, throwFalse;
	unsigned long long numInspected = 0;

	// I HATE ARITHMETIC OVERFLOW I HATE ARITHMETIC OVERFLOW
	unsigned long long doOperation(size_t index) {
		switch (operation) {
		case '+': return items.at(index) + operationAmount;
		case '-': return items.at(index) - operationAmount;
		case '*': return items.at(index) * operationAmount;
		case '/': return items.at(index) / operationAmount;
		case '^': return items.at(index) * items.at(index);
		}
	}
};


void doRound(std::vector<Monkey>& monkeys, unsigned long long lcm, size_t round) {
	for (size_t i = 0; i < monkeys.size(); ++i) {
		// Goes through each of the items that the monkey is handling
		for (size_t j = 0; j < monkeys.at(i).items.size(); ++j) {
			unsigned long long item = monkeys.at(i).items.at(j);
			item = monkeys.at(i).doOperation(j);
			item %= lcm;
			monkeys.at(i).numInspected++;

			// The monkey throws the item to another monkey based on the test
			if (item % monkeys.at(i).test == 0) {
				monkeys.at(monkeys.at(i).throwTrue).items.push_back(item);
			} else {
				monkeys.at(monkeys.at(i).throwFalse).items.push_back(item);
			}
		}

		// Now that the monkey has thrown away all the items, its empty handed
		monkeys.at(i).items.clear();
	}
}


int main() {
	// Opens the file and reads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads the input into a vector of monkeys
	std::vector<Monkey> monkeys;
	for (std::string str = ""; std::getline(ifs, str); ) {
		// Loads the line into a stream to make stuff easier later
		std::replace(str.begin(), str.end(), ',', ' ');
		std::stringstream line{ str };
		std::string token = "";

		// Checks what information the line contains and reads in the info
		line >> token;
		if (token == "Monkey") monkeys.push_back(Monkey{ });
		else if (token == "Starting") {
			line >> token;
			int num = 0;
			while (line >> num) {
				monkeys.back().items.push_back(num);
			}
		} else if (token == "Operation:") {
			line >> token >> token >> token;
			line >> monkeys.back().operation;
			line >> token;
			if (token == "old") {
				monkeys.back().operation = '^';
				monkeys.back().operationAmount = 2;
			} else {
				monkeys.back().operationAmount = std::stoi(token);
			}
		} else if (token == "Test:") {
			line >> token >> token;
			line >> monkeys.back().test;
		} else if (token == "If") {
			line >> token;
			if (token == "true:") {
				line >> token >> token >> token;
				line >> monkeys.back().throwTrue;
			} else {
				line >> token >> token >> token;
				line >> monkeys.back().throwFalse;
			}
		}
	}

	// Calculates the lcm
	unsigned long long lcm = 1;
	for (const auto& monkey : monkeys) {
		lcm *= monkey.test;
	}

	for (size_t round = 0; round < 10000; ++round) {
		doRound(monkeys, lcm, round);
	}

	// Sorts the vector of monkeys based on how many items they inspected
	std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& a, const Monkey& b) { return a.numInspected > b.numInspected; });

	// Calculates the monkey business
	unsigned long long monkey_business = monkeys.at(0).numInspected * monkeys.at(1).numInspected;
	std::cout << monkey_business << std::endl;

	return 0;
}
