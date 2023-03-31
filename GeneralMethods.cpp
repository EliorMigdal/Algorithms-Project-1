#include "GeneralMethods.h"

void isGraphDirected(Graph& mainGraph) noexcept(false) //Gets initial input from the user.
{
    char isDirected;
    cout << "Is the graph directed: y/n";
    cin >> isDirected;

    if (isDirected != 'y' && isDirected != 'n')
        throw invalidInputException();

    mainGraph.Graph::setGraphDirection(isDirected);
}

void getGraphInfo(Graph& mainGraph, int& numOfVertices, int& numOfEdges) noexcept(false)
//Gets graph's num of vertices and edges, and inserts them to the graph.
{
    int source, destination;
    cin >> numOfVertices;
    cin >> numOfEdges;

    if (numOfVertices < 0 || numOfEdges < 0)
        throw invalidInputException();

    mainGraph.Graph::setNumOfVertices(numOfVertices);

    for (int i = 0; i < numOfEdges; i++)
    {
        cin >> source;
        cin >> destination;

        if (source < 0 || destination < 0 || source > numOfVertices || destination > numOfVertices)
            throw invalidInputException();

        mainGraph.Graph::addEdge(source, destination);
    }
}