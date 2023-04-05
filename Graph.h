#pragma once
#include <vector>
#include <list>

using std::vector;
using std::list;

constexpr short int WHITE = 0;
constexpr short int GRAY = 1;
constexpr short int BLACK = 2;

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
	//Getters
	int getNumOfVertices() const;
	int getNumOfEdges() const;
	list<Trio>::iterator getVertexPos(int v) const;

	//Setters
	void setNumOfVertices(int n);
    void setGraphDirection(char);

    //Methods
	void initPos();
    void initializeEdges();
    void addEdge(int from, int to);
    bool hasEdge(int from, int to) const;
    void markEdge(int v);
    bool isVertexHasUnusedEdges(int v) const;
    bool isConnected();
    bool isEulerian();
    Graph DFS();
    void visit(Graph&, int, vector<int>&);
    Graph transposeGraph();
    vector<int> initializeColorsVector() const;
    bool visitedEntireDFSTree(vector<int>&);
    list<int> findEulerCircuit();
    list<int> findCircuit(int start);
};