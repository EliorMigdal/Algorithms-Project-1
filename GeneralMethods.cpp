#include "GeneralMethods.h"

Graph getGraphInfo() noexcept(false)
//Gets graph's num of vertices and edges, and inserts them to the graph.
{
    Graph outputGraph;

    char isDirected;
    cout << "Is the graph directed: y/n\n";
    cin >> isDirected;

    if (isDirected != 'y' && isDirected != 'n')
        throw invalidInputException();

    outputGraph.Graph::setGraphDirection(isDirected);

    int numOfVertices, numOfEdges, source, destination;
    cin >> numOfVertices;
    cin >> numOfEdges;

    if (numOfVertices <= 0 || numOfEdges <= 0)
        throw invalidInputException();

    outputGraph.Graph::setNumOfVertices(numOfVertices);

    for (int i = 0; i < numOfEdges; i++)
    {
        cin >> source;
        cin >> destination;

        if (source <= 0 || destination <= 0 || source > numOfVertices || destination > numOfVertices
                       || outputGraph.hasEdge(source, destination))
            throw invalidInputException();

        outputGraph.Graph::addEdge(source, destination);
    }
    outputGraph.initPos();
    return outputGraph;
}