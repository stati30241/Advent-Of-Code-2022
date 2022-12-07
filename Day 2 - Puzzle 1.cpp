#include <iostream>
#include <fstream>

int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	int score = 0;
	char p, o;
	while (ifs >> p >> o) {
		// Coverts the chars to a 0, 1, or 2
		p -= 65;
		o -= 88;
		score += o + 1;

		// Checks for draw or win
		if (p == o) score += 3;
		else if (o == (p + 1) % 3) score += 6;
	}

	std::cout << score << std::endl;

	return 0;
}
