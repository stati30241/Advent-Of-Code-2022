#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads the rainforest into a vector of strings
	// and calculates the width and height
	std::vector<std::string> rainforest;
	size_t width = 0, height = 0;
	std::string str = "";
	while (ifs >> str) {
		rainforest.push_back(str);
	}
	width = rainforest.front().size();
	height = rainforest.size();

	// Checks for visibility for each of the tree
	int numVisible = 0;
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j) {
			// Yes, I know there is probably a better way to do this than
			// by doing it direction by direction but its 11pm and I should
			// asleep right now
			bool visibleN = true, visibleS = true, visibleW = true, visibleE = true;

			// Checks for visibility from north
			for (int k = i - 1; k >= 0; --k) {
				if (rainforest.at(k).at(j) >= rainforest.at(i).at(j)) {
					visibleN = false;
					break;
				}
			}

			// Checks for visibility from south
			for (int k = i + 1; k < height; ++k) {
				if (rainforest.at(k).at(j) >= rainforest.at(i).at(j)) {
					visibleS = false;
					break;
				}
			}

			// Checks for visibility from west
			for (int k = j - 1; k >= 0; --k) {
				if (rainforest.at(i).at(k) >= rainforest.at(i).at(j)) {
					visibleW = false;
					break;
				}
			}

			// Checks for visibility from east
			for (int k = j + 1; k < width; ++k) {
				if (rainforest.at(i).at(k) >= rainforest.at(i).at(j)) {
					visibleE = false;
					break;
				}
			}

			// If it's visible from any direction, its visible
			if (visibleN || visibleS || visibleW || visibleE) {
				numVisible++;
			}
		}
	}

	std::cout << numVisible << std::endl;

	return 0;
}
