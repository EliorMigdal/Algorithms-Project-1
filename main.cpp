//Algorithms Assignment#1, by Ofek Shcherb and Elior Migdal.
#include "GeneralMethods.h"

int main()
{
    try
    {
        Graph mainGraph = getGraphInfo();
        list<int> eulerCircuit;
        if (mainGraph.Graph::isConnected() && mainGraph.Graph::isEulerian())
        {
            eulerCircuit = mainGraph.findEulerCircuit();
        }
        
        else
            cout << "The graph is not aulerian";

        if (!eulerCircuit.empty())
        {
            cout << "The graph is aulerian\n(";
            auto eulerIterator = eulerCircuit.begin();
            while (eulerIterator != eulerCircuit.end())
            {
                cout << *eulerIterator++;
                if (eulerIterator != eulerCircuit.end())
                    cout << ",";
            }
            cout << ")";
        }
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