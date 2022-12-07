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
		
		if (o == 0) score += (3 + (p - 1) % 3) % 3 + 1; // Wierd modulus because negative numbers
		else if (o == 1) score += p + 3 + 1;
		else if (o == 2) score += (p + 1) % 3 + 6 + 1;
	}

	std::cout << score << std::endl;

	return 0;
}
