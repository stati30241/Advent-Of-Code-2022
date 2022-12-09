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
	int maxScenicScore = 0;
	for (size_t i = 0; i < height; ++i) {
		for (size_t j = 0; j < width; ++j) {
			// Yes, I know going there is probably a better way to do this
			// than by doing it direction by direction but its 11pm and I 
			// should asleep right now
			// For puzzle 2, I just had to turn these into ints and just
			// increment them each time I did i iterated (the breaks are 
			// neccessary now instead of just being there just for 
			// optimization purposes)
			int visibleN = 0, visibleS = 0, visibleW = 0, visibleE = 0;

			// Calculates the scenic score from north
			for (int k = i - 1; k >= 0; --k) {
				visibleN++;
				if (rainforest.at(k).at(j) >= rainforest.at(i).at(j)) break;
			}

			// Calculates the scenic score from south
			for (int k = i + 1; k < height; ++k) {
				visibleS++;
				if (rainforest.at(k).at(j) >= rainforest.at(i).at(j)) break;
			}

			// Calculates the scenic score from west
			for (int k = j - 1; k >= 0; --k) {
				visibleW++;
				if (rainforest.at(i).at(k) >= rainforest.at(i).at(j)) break;
			}

			// Calculates the scenic score from east
			for (int k = j + 1; k < width; ++k) {
				visibleE++;
				if (rainforest.at(i).at(k) >= rainforest.at(i).at(j)) break;
			}

			// Calculates the trees scenic score
			int scenicScore = visibleN * visibleS * visibleW * visibleE;
			if (scenicScore > maxScenicScore) maxScenicScore = scenicScore;
		}
	}

	std::cout << maxScenicScore << std::endl;

	return 0;
}
