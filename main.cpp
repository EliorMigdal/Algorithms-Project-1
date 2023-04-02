#include "GeneralMethods.h"

int main()
{
    try
    {
        Graph mainGraph = getGraphInfo();
        if (bool checkConditions = mainGraph.Graph::isEulerian())
        {
            list<int> eulerCircuit = mainGraph.findEulerCircuit();
        }

        else
            cout << "The graph is not aulerian";

        //check if graph is connected (IGNORE FOR NOW)
            //DFS
            //Optional: check if sufficient condition is met
        //check if graph is eulerian
            //check if necessary condition is met
                //if it does, run the algorithm for finding an eulerian circle, using findCircuit
                //if it is, print euler circle
            //else, there is no circuit

        //needed methods:
        // 1. checkIfConnected (IGNORE FOR NOW)
            // DFS, visit, Transpose
        // 2. checkIfEulerian
            // checkCondition, findEulerCircuit, findCircuit

    }
    catch (generalException& error)
    {
        cout << error.what() << endl;
    }
    catch (...)
    {
        cout << generalException().what() << endl;
    }

    return 1;
}