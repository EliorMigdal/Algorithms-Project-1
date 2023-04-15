#include "Graph.h"

/*----------------------Getters----------------------*/

int Graph::getNumOfVertices() const //Returns num of vertices in graph.
{
	return n;
}

int Graph::getNumOfEdges() const //Returns num of edges in graph.
{
	return m;
}

list<Trio>::iterator Graph::getVertexPos(int v) const //Returns an iterator to current edge in graph.
{
	return pos.at(v - 1);
}

/*----------------------Setters----------------------*/

void Graph::setNumOfVertices(int _n) //Sets num of vertices and resizes data structures.
{
	adjArray.resize(_n);
	inDegrees.resize(_n, 0);
	outDegrees.resize(_n, 0);
	pos.resize(_n);
	this->n = _n;
}

void Graph::setGraphDirection(char isDirected) //Sets graph's direction.
{
    if (isDirected == 'y')
        this->directed = true;

    else
        this->directed = false;
}

/*----------------------Methods----------------------*/

void Graph::initPos() //Initializes iterators vector.
{
    for (int i = 0;  i< n; i++)
    {
        pos.at(i) = adjArray.at(i).begin();
    }
}

void Graph::initializeEdges() //Sets all edges to be unvisited.
{
    for (int i = 0; i < n; i++)
        for (auto& neighbor : adjArray.at(i))
            neighbor.visited = false;
}

void Graph::addEdge(int from, int to) //Inserts the (from, to) edge to the graph.
{
    Trio fromStruct, toStruct;
    fromStruct.vertex = from;
    toStruct.vertex = to;

    adjArray[from - 1].push_back(toStruct);
    outDegrees[from - 1]++;
    inDegrees[to - 1]++;

    if (!this->directed)
    {
        adjArray[to - 1].push_back(fromStruct);
        outDegrees[to - 1]++;
        inDegrees[from - 1]++;
        adjArray[from - 1].back().mutualPointer = &adjArray[to - 1].back();
        adjArray[to - 1].back().mutualPointer = &adjArray[from - 1].back();
    }
    m++;
}

bool Graph::hasEdge(int from, int to) const //Checks whether the edge (from, to) already exists in the graph.
{
    bool hasEdge = false;
	for (auto neighbor : adjArray[from - 1])
	{
		if (neighbor.vertex == to)
			hasEdge = true;
	}
	return hasEdge;
}

void Graph::markEdge(const int v) //Sets an edge as visited.
{
    pos.at(v - 1)->visited = true;
    if (!this->directed)
    {
        pos.at(v - 1)->mutualPointer->visited = true;
    }
}

bool Graph::isVertexHasUnusedEdges(int v) const //Returns whether we visited all of v's neighbors.
{
    return pos[v - 1] != adjArray[v - 1].end();
}

bool Graph::isConnected() //Checks whether graph is connected.
{
    bool isConnected;

    vector<int> colors = this->Graph::initializeColorsVector();
    this->Graph::visit(this->n, colors);
    this->Graph::initPos();
    this->Graph::initializeEdges();

    Graph::visitedEntireGraph(colors) ? isConnected = true : isConnected = false;

    if (isConnected && this->directed)
    {
        Graph GTranspose = this->Graph::transposeGraph();
        vector<int> tColors = this->Graph::initializeColorsVector();
        GTranspose.Graph::visit(this->n, tColors);
        Graph::visitedEntireGraph(tColors) ? isConnected = true : isConnected = false;
    }

    return isConnected;
}

bool Graph::isEulerian() //Checks whether graph in Eulerian.
{
    bool isEulerian = true;

    if (this->directed)
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

void Graph::visit(const int vertex, vector<int> & colors) //The 'visit' part of DFS algorithm.
{
    colors.at(vertex - 1) = (int)COLORS::GRAY;

    while (this->Graph::isVertexHasUnusedEdges(vertex))
    {
        if (colors.at(pos.at(vertex - 1)->vertex - 1) == (int)COLORS::WHITE)
        {
            this->Graph::markEdge(vertex);
            this->Graph::visit(pos.at(vertex - 1)->vertex, colors);
        }
        pos.at(vertex - 1)++;
    }

    colors.at(vertex - 1) = (int)COLORS::BLACK;
}

Graph Graph::transposeGraph() //Transforms graph to G-transpose.
{
    Graph output;
    if (!this->directed)
        output = *this;

    else
    {
        output.Graph::setNumOfVertices(n);
        output.Graph::setGraphDirection('y');
        for (int i = 0; i < this->n; i++)
        {
            for (auto &neighbor: adjArray.at(i))
            {
                output.addEdge(neighbor.vertex, i + 1);
            }
        }
    }

    output.Graph::initPos();

    return output;
}

vector<int> Graph::initializeColorsVector() const //Sets all vertices as whites.
{
    vector<int> output;
    output.resize(n, (int)COLORS::WHITE);

    return output;
}

bool Graph::visitedEntireGraph(vector<int> & colors) //Checks whether DFS tree is connected.
{
    bool output = true;

    for (int vertex : colors)
        if (vertex != (int)COLORS::BLACK)
            output = false;

    return output;
}

list<int> Graph::findEulerCircuit() //Finds an euler circuit in the graph.
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

list<int> Graph::findCircuit(const int start) //Finds a circuit in the graph.
{
    int v = start;
    list<int> circuit;
    circuit.push_back(start);
    int temp;

    while(this->Graph::isVertexHasUnusedEdges(v))
    {
        while (pos.at(v - 1) != adjArray.at(v - 1).end() && pos.at(v - 1)->visited)
            //For cases that v's iterator is pointing at a visited edge.
        {
            pos.at(v - 1)++;
        }

        if (pos.at(v - 1) != adjArray.at(v - 1).end())
        {
            this->Graph::markEdge(v);
            circuit.push_back(pos.at(v - 1)->vertex);
            temp = v;
            v = pos.at(v - 1)->vertex;
            pos.at(temp - 1)++;
        }
    }

    return circuit;
}