#include "GeneralMethods.h"

int main()
{
    int numOfVertices, numOfEdges;
    Graph mainGraph;
    try
    {
        isGraphDirected(mainGraph);
        getGraphInfo(mainGraph, numOfVertices, numOfEdges);
    }
    catch (generalException& error)
    {
        cout << error.what() << endl;
    }
    catch (...)
    {
        cout << generalException().what() << endl;
    }
    //check if graph is connected
    //check if graph is eulerian
        //if it is, print euler circle

    return 1;
}