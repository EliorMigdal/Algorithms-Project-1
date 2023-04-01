#pragma once
#include <vector>
#include <list>

using std::vector;
using std::list;

struct Trio
{
    int vertex;
    bool visited;
    Trio* mutualPointer = nullptr;
};

class Graph
{
	//Attributes
	int n;
	int m;
	vector<list<Trio>> adjArray;
	vector<list<Trio>::iterator> pos;
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
    void setGraphDirection(char);

	//Methods
	bool addEdge(int from, int to);
	bool hasEdge(int from, int to);
	bool isEulerian();
	bool isConnected();
	list<int>& findEulerCircuit();
	list<int>& findCircuit();
};