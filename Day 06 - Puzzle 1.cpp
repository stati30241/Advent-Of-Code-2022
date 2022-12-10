#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads the content of the file into the buffer
	std::string buffer = "";
	ifs >> buffer;

	size_t index = 0;
	for (size_t i = 0; i < buffer.size() - 4; ++i) {
		// An efficient algorithm for checking for repeating elements
		// (might be overkill here)
		std::map<char, int> charCount;
		bool charRepeat = false;
		for (size_t j = i; j < i + 4; ++j) {
			if (charCount[buffer.at(j)] == 1) charRepeat = true;
			else charCount[buffer.at(j)] = 1;
		}

		// If none of the characters repeated, then we break
		if (!charRepeat) {
			index = i + 4;
			break;
		}
	}

	std::cout << index << std::endl;

	return 0;
}
