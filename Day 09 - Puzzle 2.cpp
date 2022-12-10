#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

int main() {
	// Opens the file and loads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Tracks the positions of the head and tail and
	// the coordinates visited by the tail
	// (Unordered) Set datastructure used because we
	// do not want any duplicate coordinates
	std::vector<std::pair<int, int>> rope{ 10, std::make_pair(0, 0) };
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

		// Moves the rope
		for (size_t i = 0; i < mag; ++i) {
			// "Moves" the head
			std::vector<std::pair<int, int>> newRope = rope;
			newRope.front().first += normal.first;
			newRope.front().second += normal.second;

			// Moves the rest of the rope
			for (size_t r = 1; r < rope.size(); ++r) {
				// Checks if the knot is in contact with the previous one
				bool inContact = false;
				for (int j = rope.at(r).first - 1; j <= rope.at(r).first + 1; ++j) {
					for (int k = rope.at(r).second - 1; k <= rope.at(r).second + 1; ++k) {
						if (j == newRope.at(r - 1).first && k == newRope.at(r - 1).second) inContact = true;
					}
				}

				// If the knot isn't in contact, then move to a new position
				// where it is in contact
				if (!inContact) {
					// This next part is a mess, even I barely know how it works
					if (rope.at(r).first == newRope.at(r - 1).first) {
						if (rope.at(r - 1).first != newRope.at(r - 1).first) {
							newRope.at(r).first = newRope.at(r - 1).first;
							newRope.at(r).second = rope.at(r - 1).second;
						} else {
							newRope.at(r) = rope.at(r - 1);
						}
					} else if (rope.at(r).second == newRope.at(r - 1).second) {
						if (rope.at(r - 1).second != newRope.at(r - 1).second) {
							newRope.at(r).first = rope.at(r - 1).first;
							newRope.at(r).second = newRope.at(r - 1).second;
						} else {
							newRope.at(r) = rope.at(r - 1);
						}
					} else {
						if (rope.at(r).first == rope.at(r - 1).first) {
							newRope.at(r).first = newRope.at(r - 1).first;
							newRope.at(r).second = rope.at(r - 1).second;
						} else if (rope.at(r).second == rope.at(r - 1).second) {
							newRope.at(r).first = rope.at(r - 1).first;
							newRope.at(r).second = newRope.at(r - 1).second;
						} else {
							newRope.at(r) = rope.at(r - 1);
						}
					}

					// If the tail moved, then note down its position
					if (r == 9) {
						std::string str = std::to_string(newRope.at(r).first) + ", " + std::to_string(newRope.at(r).second);
						coordsVisited.insert(str);
					}
				}
			}

			rope = newRope;
		}
	}

	std::cout << coordsVisited.size() << std::endl;

	return 0;
}
