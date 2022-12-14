#include <algorithm>
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <vector>


// Simple node structure to do pathfinding with
struct Node {
	int x, y;
	char elevation;
	Node* parent;
	size_t gCost = 0;
	size_t hCost = 0;
	size_t fCost = 0;
	bool visited = false;

	bool operator== (const Node& other) {
		return (x == other.x && y == other.y);
	}
};


int main() {
	// Opens the file and reads it into a stream
	std::ifstream ifs{ "input.txt" };
	if (!ifs.is_open()) return -1;

	// Reads the input into a 2d vector of nodes
	// and calculates the position of the start 
	// and end nodes
	std::vector<std::vector<Node*>> heightMap;
	Node* startNode = new Node{};
	Node* endNode = new Node{};
	for (std::string str = ""; std::getline(ifs, str); ) {
		std::vector<Node*> row;
		for (size_t i = 0; i < str.size(); ++i) {
			Node* node = new Node{ static_cast<int>(i), static_cast<int>(heightMap.size()) };
			switch (str.at(i)) {
			case 'S':
				startNode = node;
				startNode->elevation = 'a';
				row.push_back(startNode);
				break;
			case 'E':
				endNode = node;
				endNode->elevation = 'z';
				row.push_back(endNode);
				break;
			default:
				node->elevation = str.at(i);
				row.push_back(node);
				break;
			}
		}
		heightMap.push_back(row);
	}

	// Breadth first search for path finding
	std::queue<Node*> queue;
	queue.push(startNode);
	while (!queue.empty()) {
		// Gets the current node
		Node* currentNode = queue.front();
		queue.pop();

		// Breaks out of the loop is we reached the end
		if (*currentNode == *endNode) break;

		for (int i = currentNode->x - 1; i <= currentNode->x + 1; ++i) {
			for (int j = currentNode->y - 1; j <= currentNode->y + 1; ++j) {
				// The node cannot be a neighbor of itself and must be
				// stricly in one of the four cardinal directions
				if ((currentNode->x == i && currentNode->y == j) ||
					((currentNode->x != i && currentNode->y != j))) continue;

				// If the neighbor is out of bounds continue onto the next neighbor
				if (i < 0 || i >= heightMap.at(0).size() || j < 0 || j >= heightMap.size()) continue;

				// If the node is unclimbable or closed, move onto the next node
				Node* neighbor = heightMap.at(j).at(i);
				if (currentNode->elevation + 1 < neighbor->elevation) continue;
				if (neighbor->visited) continue;

				neighbor->visited = true;
				neighbor->parent = currentNode;
				queue.push(neighbor);
			}
		}
	}
	
	size_t steps = 0;
	Node* lastNode = endNode;
	while (lastNode != startNode) {
		lastNode = lastNode->parent;
		steps++;
	}

	std::cout << steps << std::endl;

	return 0;
}
