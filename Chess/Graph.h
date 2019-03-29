#pragma once
#include <vector>

class Graph {

private:

	struct Edge {
		int startNode;
		int endNode;
	};

	std::vector<std::vector<int>> adjacencyList;
public:
	Graph(int size);
};