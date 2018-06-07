#include "/home/ls/Graphs/include/GraphOperations.h"
#include "/home/ls/Graphs/include/Pathfinder.h"
//Nice and simple menu for a change. I dont even feel bad for making it
using namespace std;

int main()
{
    Initialize();
    int graphSize;
    cout << "Input correct graph size or input anything else to load graph from file " << endl;
    cin >> graphSize;
    if(graphSize <= 2 || graphSize > 1000) {
        cout << "Loading graph from file. Input filename ";
        string filename;
        cin >> filename;
        graphSize = 0;
        graphSize = ReadGraph(filename, graphSize);
        if(!graphSize) return 0;
    }else {
        GenerateGraph(graphSize);
    }
    GiveLengths(graphSize);
    bool run = 1;
    while(run) {
        cout << "\t\tMenu\n";
        cout << "1) Finding path between two vertices   2) Shimbell's algorithm\n";
        cout << "3) Get a matrix with shortest paths    4) Get shortest paths from one vertex\n";
        cout << "5) Find minimal spanning tree          6) Count the spanning trees\n";
        cout << "7) Euler and Hamilton cycles           8) Find the mincost flow\n";
        cout << "9) Input new graph                     0) Quit\n";

        int num;
        cin >> num;
        switch(num) {
            case 1:
            {
                std::cout << "Input pair of vertices to find path or zero to quit ";
                int a, b;
                cin >> a;
                if(a <= 0 || a > graphSize) {
                    break;
                }
                cin >> b;
                if(b <= 0 || b > graphSize) {
                    break;
                }
                for(int i = 0; i < graphSize; ++i) marked[i] = 0;
                if(bfs(a - 1, b - 1, graphSize)) {
                    std::cout << "Yes\n";
                }else{
                    std::cout << "No\n";
                }
                break;
            }
            case 2:
            {
                cout << "Input length for Shimbell's algorithm ";
                int pathlength;
                cin >> pathlength;
                if(pathlength <= 0 || pathlength > 1000) {
                    cout << "Incorrect path length\n";
                    break;
                }
                Shimbell(pathlength, graphSize);
                break;
            }
            case 3:
            {
                cout << "Matrix of shortest paths:\n";
                Floyd(graphSize);
                break;
            }
            case 4:
            {
                cout << "Input vertex: ";
                int v;
                cin >> v;
                if(v <= 0 || v > graphSize) {
                    cout << "Incorrect vertex number. Setting vertex number to one\n";
                    v = 1;
                }
                cout << "Dijkstra:\n";
                Dijkstra(v-1, graphSize);
                cout << "Ford-Bellman:\n";
                FordBellman(v-1, graphSize);
                break;
            }
            case 5:
            {
                cout << "Minimum spanning tree:\n";
                cout << "Kruskal:\n";
                Kruskal(graphSize);
                cout << "Prim:\n";
                Prim(graphSize);
                cout << "Pruffer code:\n";
                Pruffer(graphSize);
                break;
            }
            case 6:
            {
                cout << "Number of spanning trees is ";
                Kirhgoff(graphSize);
                break;
            }
            case 7:
            {
                if(graphSize < 32) {
                    cout << "Finding the Hamilton cycles\n";
                    MakeHamilton(graphSize);
                    Hamilton(graphSize, 1, 0);
                    PrintHamilton();
                    cout << "\nAdding the Euler cycle\n";
                    MakeEuler(graphSize);
                    Euler(graphSize);
                } else {
                    cout << "Graph is too big\n";
                }
                break;
            }
            case 8:
            {
                cout << "Giving capacities\n";
                InitializeFlows(graphSize);
                FindMincostFlow(graphSize);
                break;
            }
            case 9:
            {
                Initialize();
                cout << "Input correct graph size or input anything else to load graph from file " << endl;
                cin >> graphSize;
                if(graphSize <= 2 || graphSize > 1000) {
                    cout << "Loading graph from file. Input filename ";
                    string filename;
                    cin >> filename;
                    graphSize = 0;
                    graphSize = ReadGraph(filename, graphSize);
                    if(!graphSize) return 0;
                } else {
                    GenerateGraph(graphSize);
                }
                GiveLengths(graphSize);
                break;
            }
            case 0:
            {
                cout << "Ending program\n";
                run = 0;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return 0;
}
