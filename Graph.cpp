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

bool Graph::setNumOfVertices(int _n)
{
	if (_n < 0)
	{
		return false;
	}

	adjArray.resize(_n);
	inDegrees.resize(_n, 0);
	outDegrees.resize(_n, 0);
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

    Trio* fromStruct = new Trio{from, false};
    Trio* toStruct = new Trio{to, false};
    fromStruct->mutualPointer = toStruct;
    toStruct->mutualPointer = fromStruct;

	adjArray[from - 1].push_back(*toStruct);
	outDegrees[from - 1]++;
	inDegrees[to - 1]++;
	
	if (!directed)
	{
		adjArray[to - 1].push_back(*fromStruct);
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

list<int>& Graph::findEulerCircuit()
{
	list<int> EulerCircuit;

//    EulerCircuit = findCircuit(*this, 1);

    auto outputIterator = EulerCircuit.begin();

    while (outputIterator != EulerCircuit.end())
    {
        if (this->pos.at(*outputIterator-1) != adjArray.at(*outputIterator-1).end())
        {
//            list<int> innerList = findCircuit(*this, vertex);
//            for (vertex : innerList)
//                EulerCircuit.insert(outputIterator, vertex);
        }
    }

	return EulerCircuit;
}

list<int>& Graph::findCircuit()
{
	list<int> circuit;
	return circuit;
}