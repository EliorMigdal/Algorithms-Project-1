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
	int n = 0;
	int m = 0;
	vector<list<Trio>> adjArray;
	vector<list<Trio>::iterator> pos;
	vector<int> inDegrees;
	vector<int> outDegrees;
	bool directed = false;

public:
	//Empty constructor

	//Getters
	int getNumOfVertices() const;
	int getNumOfEdges() const;
	list<Trio>::iterator getVertexPos(const int v) const;
	

	//Setters
	void setNumOfVertices(int n);
    void setGraphDirection(char);


	//Methods
	void initPos();
	void addEdge(const int from, const int to);
	bool hasEdge(const int from, const int to);
	bool isEulerian();
	bool isConnected();
	list<int> findEulerCircuit();
	list<int> findCircuit(const int start);
	bool isVertexHasUnusedEdges(const int v) const;
	void markEdge(const int v);
};