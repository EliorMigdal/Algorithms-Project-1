#include "Graph.h"

/*--------------------Constructor--------------------*/

Graph::Graph(char directed)
{
	n = 0;
	m = 0;
	if (directed == 'y')
	{
		this->directed = true;
	}
	else
	{
		this->directed = false;
	}
}

/*----------------------Getters----------------------*/

int Graph::getNumOfVertices() const
{
	return n;
}

int Graph::getNumOfEdges() const
{
	return m;
}

/*----------------------Setters----------------------*/

bool Graph::setNumOfVertices(int n)
{
	if (n < 0)
	{
		return false;
	}

	adjArray.resize(n);
	inDegrees.resize(n, 0);
	outDegrees.resize(n, 0);
	this->n = n;
	return true;
}

void Graph::setGraphDirection(char isDirected)
{
    this->directed = isDirected;
}

/*----------------------Methods----------------------*/

bool Graph::addEdge(int from, int to)
{
	if (from < 1 || from > n)
	{
		return false;
	}

	if (to < 1 || to > n)
	{
		return false;
	}

	if (hasEdge(from, to))
	{
		return false;
	}

    Trio fromStruct = Trio{from, false};
    Trio toStruct = Trio{to, false};
    fromStruct.mutualPointer = &toStruct;
    toStruct.mutualPointer = &fromStruct;

	adjArray[from - 1].push_back(fromStruct);
	outDegrees[from - 1]++;
	inDegrees[to - 1]++;
	
	if (!directed)
	{
		adjArray[to - 1].push_back(toStruct);
		outDegrees[to - 1]++;
		inDegrees[from - 1]++;
	}
	m++;
	return true;
}

bool Graph::hasEdge(int from, int to)
{
	list<Trio> adjList = adjArray[from - 1];
	for (auto neighbor : adjList)
	{
		if (neighbor.vertex == to)
			return true;
	}

	return false;
}

bool Graph::isEulerian()
{
	return true;
}

bool Graph::isConnected()
{
	return true;
}

list<int>& Graph::findEulerCircuit()
{
	list<int> EulerCircuit;
	return EulerCircuit;
}

list<int>& Graph::findCircuit()
{
	list<int> circuit;
	return circuit;
}