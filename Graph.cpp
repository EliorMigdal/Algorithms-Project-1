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

list<Trio>::iterator Graph::getVertexPos(const int v)
{
	return pos.at(v);
}

/*----------------------Setters----------------------*/

bool Graph::setNumOfVertices(int _n)
{
	if (_n < 0)
	{
		return false;
	}

	adjArray.resize(_n);
	inDegrees.resize(_n, 0);
	outDegrees.resize(_n, 0);
	pos.resize(_n);
	this->n = _n;
	return true;
}

void Graph::setGraphDirection(char isDirected)
{
    if (isDirected == 'y')
        this->directed = true;

    else
        this->directed = false;
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

    Trio fromStruct = {from, false};
    Trio toStruct = {to, false};
    

	adjArray[from - 1].push_back(toStruct);
	outDegrees[from - 1]++;
	inDegrees[to - 1]++;
	
	if (adjArray[from - 1].size() == 1)
	{
		pos.at(from - 1) = adjArray.at(from-1).begin();
	}
	if (!directed)
	{
		adjArray[to - 1].push_back(fromStruct);
		outDegrees[to - 1]++;
		inDegrees[from - 1]++;
		if (adjArray[to - 1].size() == 1)
		{
			pos[to - 1] = adjArray[to - 1].begin();
		}
		adjArray[from - 1].back().mutualPointer = &adjArray[to - 1].back();
		adjArray[to - 1].back().mutualPointer = &adjArray[from - 1].back();
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
    bool isEulerian = true;

    if (directed)
    {
        auto inIterator = inDegrees.begin();
        auto outIterator = outDegrees.begin();

        while (inIterator != inDegrees.end() && outIterator != outDegrees.end() && isEulerian)
        {
            if (*inIterator != *outIterator)
                isEulerian = false;

            inIterator++;
            outIterator++;
        }
    }

    else
    {
        auto degIterator = inDegrees.begin();

        while (degIterator != inDegrees.end() && isEulerian)
        {
            if (*degIterator % 2 != 0)
                isEulerian = false;

            degIterator++;
        }
    }

    return isEulerian;
}

bool Graph::isConnected()
{
	return true;
}

list<int> Graph::findEulerCircuit()
{
	list<int> EulerCircuit;

    EulerCircuit = findCircuit(1);

    auto outputIterator = EulerCircuit.begin();

    while (outputIterator != EulerCircuit.end())
    {
        if (this->pos.at(*outputIterator-1) != adjArray.at(*outputIterator-1).end())
        {
            list<int> innerList = findCircuit(*outputIterator);
            EulerCircuit.insert(outputIterator, innerList.begin(), innerList.end());
        }
		outputIterator++;
    }

	return EulerCircuit;
}

list<int> Graph::findCircuit(const int start)
{
	int v = start;
	list<int> circuit;
	circuit.push_back(start - 1);

	while(isVertexHasUnusedEdges(v - 1))
	{
		auto neighbor = getVertexPos(v - 1);
		markEdge(v - 1, *neighbor);
		circuit.push_back(neighbor->vertex);
		v = neighbor->vertex;
	}

	return circuit;
}

bool Graph::isVertexHasUnusedEdges(const int v)
{
	return pos[v] != adjArray[v].end();
}

void Graph::markEdge(const int v, Trio& neighbor)
{
	neighbor.visited = true;
	if (!directed)
	{
		neighbor.mutualPointer->visited = true;
	}
	while (pos.at(v) != adjArray.at(v).end() && pos.at(v)->visited == true)
	{
		pos.at(v)++;
	}
}

