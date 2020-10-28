/* Graph read from file, and represnted as adjacency list. 
To implement DFS and BFS on the graph
*/
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
void DFSHelper(const adjlist& alist, vector<int>& dfslist, vector<bool>& visited, int source);
void printQ(queue<int> qcopy);


// DFS - returns list of nodes in DFS order starting from source vertex
vector<int> DFS(const adjlist& alist, int source) {

    vector<bool>vis(alist.size(), false);
    vector<int>depth;

    DFSHelper(alist, depth, vis, source);

    return depth;
}

void DFSHelper(const adjlist& alist, vector<int>& dfslist, vector<bool>& visited, int source) {

    dfslist.push_back(source);
    visited[source] = true;

    for(auto& element: alist[source]){
        if(visited[element.first] == false){
            DFSHelper(alist, dfslist, visited, element.first);
        }
    }
}

// BFS - returns list of nodes in BFS order starting from source vertex
vector<int> BFS(const adjlist& alist, int source) {

    int iter;
    queue<int> temp;
    vector<int>bread;
    vector<bool> vis(alist.size(), false);
    
    temp.push(source);
    vis[source] = true;

    while(!temp.empty()){
        iter = temp.front();
        temp.pop();
        bread.push_back(iter);
        
        for(auto& element : alist[iter]){
            if( vis[element.first] == false){
                vis[element.first] = true;
                temp.push(element.first);
            }
        }
    }
    return bread;
}




// Reads a csv graph from file and returns an adjacency list
adjlist makeGraph(ifstream& ifs) {
    int vh, vt, wt;
    string line;
    unordered_multimap<int, pair<int, int>> elist;
    set<int> vlist;
    
    while (getline(ifs, line)) {
        stringstream ss(line);
        ss >> vt;
        if (ss.peek() == ',')
            ss.ignore();
        ss >> vh;
        if (ss.peek() == ',')
            ss.ignore();
        ss >> wt;

        elist.emplace(vt, make_pair(vh, wt));   
        vlist.insert(vt);
        vlist.insert(vh);
    }
    
    adjlist res(vlist.size()); // Preallocate vector
    
    for (auto& ele : elist) {
        res.at(ele.first).push_back(make_pair(ele.second.first, ele.second.second));
    }
    return res;
}

// Prints the adjacency list (only vertices, not edge weights)
void printGraph(const adjlist& alist) {
    int i = 0;
    for (auto& v : alist) {
        cout << i++ << ": ";
        for (auto& av : v) {
            cout << av.first << " ";
        }
        cout << endl;
    }
}

// Prints queue for debugging
void printQ(queue<int> qcopy) {
    while (!qcopy.empty()) {
        cout << qcopy.front();
        qcopy.pop();
    }
    cout << endl;
}





