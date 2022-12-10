#include <iostream>
#include <fstream>
#include <string>

int main() {
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	int sum = 0;
	std::string items = "";
	while (ifs >> items) {
		// Compares each char in compartment 1 and 2
		for (size_t i = 0; i < items.size() / 2; ++i) {
			for (size_t j = items.size() / 2; j < items.size(); ++j) {
				if (items.at(i) == items.at(j)) {
					sum += std::isupper(items.at(i)) ? (items.at(i) - 64 + 26) : (items.at(i) - 96);
					goto break_out; // <-- Very evil never use (but if it works, it works)
				}
			}
		}
	break_out:;
	}

	std::cout << sum << std::endl;

	return 0;
}
