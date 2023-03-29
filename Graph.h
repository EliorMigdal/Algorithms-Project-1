#pragma once
#include <vector>
#include <list>

using std::vector;
using std::list;
class Graph
{
	//Attributes
	int n;
	int m;
	vector<list<int>> adjArray;
	vector<list<int>::iterator> pos;
	vector<int> inDegrees;
	vector<int> outDegrees;
	bool directed;

public:
	//Empty constructor
	Graph(char directed = 'n');

	//Getters
	int getNumOfVertices() const;
	int getNumOfEdges() const;

	//Setters
	bool setNumOfVertices(int n);

	//Methods
	bool addEdge(int from, int to);
	bool hasEdge(int from, int to);
	bool isEulerian();
	bool isConnected();
	const list<int>& findEulerCircuit();
	const list<int>& findCircuit();
};


