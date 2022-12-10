#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Tracks the positions of the head and tail and
	// the coordinates visited by the tail
	// (Unordered) Set datastructure used because we
	// do not want any duplicate coordinates
	std::pair<int, int> headPos = std::make_pair(0, 0);
	std::pair<int, int> tailPos = std::make_pair(0, 0);
	std::unordered_set<std::string> coordsVisited;
	coordsVisited.insert("0, 0");
	
	// The direction the head travels and by how much
	char dir = 0;
	int mag = 0;
	while (ifs >> dir >> mag) {
		// Calculates the normal vector for the head to travel
		std::pair<int, int> normal = std::make_pair(0, 0);
		switch (dir) {
		case 'U':
			normal = { 0,  1 };
			break;
		case 'D':
			normal = { 0, -1 };
			break;
		case 'R':
			normal = {  1, 0 };
			break;
		case 'L':
			normal = { -1, 0 };
			break;
		}

		// Moves the head and the tail
		for (size_t i = 0; i < mag; ++i) {
			// "Moves" the head 
			std::pair<int, int> newHeadPos = headPos;
			newHeadPos.first += normal.first;
			newHeadPos.second += normal.second;
			
			// Checks if the head and tail are in contact
			bool tailInContact = false;
			for (int j = tailPos.first - 1; j <= tailPos.first + 1; ++j) {
				for (int k = tailPos.second - 1; k <= tailPos.second + 1; ++k) {
					if (j == newHeadPos.first && k == newHeadPos.second) tailInContact = true;
				}
			}
			
			// If the tail isn't in contact then move it to the last head position
			if (!tailInContact) {
				tailPos = headPos;
				std::string str = std::to_string(tailPos.first) + ", " + std::to_string(tailPos.second);
				coordsVisited.insert(str);
			}

			headPos = newHeadPos;
		}
	}

	std::cout << coordsVisited.size() << std::endl;

	return 0;
}
