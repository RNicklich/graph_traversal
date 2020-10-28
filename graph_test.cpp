/* Test for BFS and DFS */
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <set>
#include <queue>

using namespace std;

// Each vertex has an integer id. 

typedef vector<vector<pair<int,int>>> adjlist; // Pair: (head vertex, edge weight)
adjlist makeGraph(ifstream& ifs);
void printGraph(const adjlist& alist);
vector<int> BFS(const adjlist& alist, int source); // Return vertices in BFS order
vector<int> DFS(const adjlist& alist, int source);  // Return vertices in DFS order

int main() {
    ifstream ifs("sample_edges.txt");
    adjlist alist = makeGraph(ifs);
    printGraph(alist);
    vector<int> dfslist = DFS(alist, 0);
    for (auto& ele : dfslist) // Prints 0 2 4 5 1 3 
        cout << ele << " ";
    cout << endl;
    
    vector<int> bfslist = BFS(alist, 0);
    for (auto& ele : bfslist) // Prints 0 2 1 4 3 5 
        cout << ele << " ";
    cout << endl;

}