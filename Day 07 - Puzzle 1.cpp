#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Map that contains the size of each directory
	std::map<std::string, int> dirs;

	// The current directories that we are into
	std::vector<std::string> currentDirs;
	std::string input, prevInput;

	// Loops over each word
	while (ifs >> input) {
		// If we are changing directory, then we should update the
		// current_directories vector, unless we are moving out one
		// level, where we pop out the last directory we were in
		if (prevInput == "cd") {
			if (input == "..") currentDirs.pop_back();
			else {
				currentDirs.push_back(input);

				// Constructs a unique string for each directory
				// based on their location (to avoid name collision)
				std::string currentDir = "";
				for (std::string str : currentDirs) {
					currentDir += str + "/";
				}
				dirs[currentDir] = 0;
			}
		}

		// Checks if the input was a number
		bool isNumber = true;
		for (char ch : input) {
			if (!std::isdigit(ch)) isNumber = false;
		}
		
		// If it was a number, then it was the size of a file,
		// so we add that file size to the size of each of the
		// directories in current_directories
		if (isNumber) {
			for (size_t i = 0; i < currentDirs.size(); ++i) {
				std::string currentDir = "";
				for (size_t j = 0; j <= i; ++j) {
					currentDir += currentDirs.at(j) + "/";
				}
				dirs[currentDir] += std::stoi(input);
			}
		}

		prevInput = input;
	}

	// Sums up the sizes of the directories with a size
	// of at most 100000
	int sum = 0;
	for (const auto& key : dirs) {
		if (key.second <= 100000) sum += key.second;
	}

	std::cout << sum << std::endl;

	return 0;
}
