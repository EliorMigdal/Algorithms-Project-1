#pragma once
#include <vector>
#include <list>

using std::vector;
using std::list;

struct Trio
{
    int vertex = 0;
    bool visited = false;
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
	list<Trio>::iterator getVertexPos(const int v);
	

	//Setters
	bool setNumOfVertices(int n);
    void setGraphDirection(char);


	//Methods
	bool addEdge(const int from, const int to);
	bool hasEdge(const int from, const int to);
	bool isEulerian();
	bool isConnected();
	list<int> findEulerCircuit();
	list<int> findCircuit(const int start);
	bool isVertexHasUnusedEdges(const int v);
	void markEdge(const int v, Trio& neighbor);
};