#include "Graph.h"

/*--------------------Constructor--------------------*/


/*----------------------Getters----------------------*/

int Graph::getNumOfVertices() const
{
	return n;
}

int Graph::getNumOfEdges() const
{
	return m;
}

list<Trio>::iterator Graph::getVertexPos(const int v) const
{
	return pos.at(v - 1);
}

/*----------------------Setters----------------------*/

void Graph::setNumOfVertices(int _n)
{
	adjArray.resize(_n);
	inDegrees.resize(_n, 0);
	outDegrees.resize(_n, 0);
	pos.resize(_n);
	this->n = _n;
}

void Graph::setGraphDirection(char isDirected)
{
    if (isDirected == 'y')
        this->directed = true;

    else
        this->directed = false;
}

/*----------------------Methods----------------------*/

void Graph::addEdge(const int from, const int to)
{
    Trio fromStruct = {from, false};
    Trio toStruct = {to, false};
    
	adjArray[from - 1].push_back(toStruct);
	outDegrees[from - 1]++;
	inDegrees[to - 1]++;
	
	if (!directed)
	{
		adjArray[to - 1].push_back(fromStruct);
		outDegrees[to - 1]++;
		inDegrees[from - 1]++;
		adjArray[from - 1].back().mutualPointer = &adjArray[to - 1].back();
		adjArray[to - 1].back().mutualPointer = &adjArray[from - 1].back();
	}
	m++;
}

bool Graph::hasEdge(const int from, const int to)
{
	for (auto neighbor : adjArray[from - 1])
	{
		if (neighbor.vertex == to)
			return true;
	}
	return false;
}

bool Graph::isEulerian()
{
    bool isEulerian = true;
	if (!isConnected())
		isEulerian = false;

    else if (directed)
    {

        auto inIterator = inDegrees.begin();
        auto outIterator = outDegrees.begin();

        while (inIterator != inDegrees.end() && outIterator != outDegrees.end() && isEulerian)
        {
            if (*inIterator != *outIterator || *inIterator == 0 || *outIterator == 0)
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
            if (*degIterator % 2 != 0 || *degIterator == 0)
                isEulerian = false;

            degIterator++;
        }
    }

    return isEulerian;
}

bool isConnected()
{
	return true;
}

list<int> Graph::findEulerCircuit()
{
	list<int> EulerCircuit;
	list<int> innerCircuit;

    EulerCircuit = findCircuit(1);

    auto outputIterator = EulerCircuit.begin();

    while (outputIterator != EulerCircuit.end())
    {
        if (isVertexHasUnusedEdges(*outputIterator))
        {
			innerCircuit = findCircuit(*outputIterator);
			auto temp = outputIterator;
            EulerCircuit.insert(++outputIterator, ++innerCircuit.begin(), innerCircuit.end());
			outputIterator = temp;
        }

		outputIterator++;
    }

	return EulerCircuit;
}

list<int> Graph::findCircuit(const int start)
{
	int v = start;
	list<int> circuit;
	circuit.push_back(start);
	int temp;

	while(isVertexHasUnusedEdges(v))
	{
		while (pos.at(v - 1) != adjArray.at(v - 1).end() && pos.at(v - 1)->visited == true)
		{
			pos.at(v - 1)++;
		}

		if (pos.at(v - 1) != adjArray.at(v - 1).end())
		{
			markEdge(v);
			circuit.push_back(pos.at(v - 1)->vertex);
			temp = v;
			v = pos.at(v - 1)->vertex;
			pos.at(temp - 1)++;
		}
	}

	return circuit;
}

bool Graph::isVertexHasUnusedEdges(const int v) const
{
	return pos[v - 1] != adjArray[v - 1].end();
}

void Graph::markEdge(const int v)
{
	pos.at(v - 1)->visited = true;
	if (!directed)
	{
		pos.at(v - 1)->mutualPointer->visited = true;
	}

}

void Graph::initPos()
{
	for (int i = 0;  i< n; i++)
	{
		pos.at(i) = adjArray.at(i).begin();
	}
}

