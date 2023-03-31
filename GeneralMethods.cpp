#include "GeneralMethods.h"

char isGraphDirected() noexcept(false) //Gets initial input from the user.
{
    char isDirected;
    cout << "Is the graph directed: y/n";
    cin >> isDirected;

    if (isDirected != 'y' && isDirected != 'n')
        throw invalidInputException();

    return isDirected;
}

void getGraphInfo(int& numOfVertices, int& numOfEdges) noexcept(false) //Gets graph's num of vertices and edges.
{
    cin >> numOfVertices;
    cin >> numOfEdges;

    if (numOfVertices < 0 || numOfEdges < 0)
        throw invalidInputException();
}