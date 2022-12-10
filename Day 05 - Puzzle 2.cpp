#include <iostream>
#include <fstream>
#include <stack>
#include <sstream>
#include <string>
#include <vector>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt " };
	if (!ifs.is_open()) return -1;

	// Gets and stores each of the lines containing the stacks
	std::vector<std::string> lines;
	for (std::string str = ""; std::getline(ifs, str); ) {
		if (str.at(1) == '1') break;
		lines.push_back(str);
	}
	
	// Fetches one more line to get rid of the black line
	std::string strDiscard = "";
	std::getline(ifs, strDiscard);

	// Goes backwards throught the lines, and creates a vector of vectors
	// that store the characters representing the crates
	// The main change from puzzle 1 is that now the stacks don't behave
	// like stacks, since the crane can move more than one at a time
	size_t numStacks = (lines.at(0).size() + 1) / 4;
	std::vector<std::vector<char>> supplies{ numStacks, std::vector<char>{} };
	for (int i = lines.size() - 1; i >= 0; --i) {
		for (size_t j = 1; j < lines.at(i).size(); j += 4) {
			char a = lines.at(i).at(j);
			if (a == ' ') continue;

			supplies.at((j - 1) / 4).push_back(a);
		}
	}

	// Reads and executes the procedure line by line
	for (std::string str = ""; std::getline(ifs, str); ) {
		// Reads the procedure line
		std::stringstream line{ str };
		std::string instr = "";
		size_t a, b, c;
		line >> instr >> a >> instr >> b >> instr >> c;
		// Note to self: b and c go minus 1
		
		// Moves the crates
		std::vector<char> cratesMoved{ supplies.at(b - 1).end() - a, supplies.at(b - 1).end() }; // Iterator fuckery
		supplies.at(b - 1).erase(supplies.at(b - 1).end() - a, supplies.at(b - 1).end());
		supplies.at(c - 1).insert(supplies.at(c - 1).end(), cratesMoved.begin(), cratesMoved.end()); // More iterator fuckery
	}

	// Gets the top crate of each stack and builds the string
	std::string output = "";
	for (const auto& stack : supplies) {
		output += stack.back();
	}
	std::cout << output << std::endl;

	return 0;
}
