#include "RouteOptimization.h"
#include <unordered_set>
#include <queue>

// constructor
RouteOptimization::RouteOptimization() {
    // Node -> {(Neighbor, Weight)}
    graph["A"] = {{"B", 10}, {"C", 15}};
    graph["B"] = {{"D", 12}, {"I", 11}};
    graph["C"] = {{"E", 10}};
    graph["D"] = {{"F", 2}, {"H", 14}};
    graph["E"] = {{"F", 5}, {"G", 4}};
    graph["F"] = {{"G", 3}};
    graph["G"] = {{"H", 8}};
    graph["H"] = {{"I", 7}};
    graph["I"] = {{"J", 6}};
    graph["J"] = {{"A", 9}};
}

// function to display the adjacency list
void RouteOptimization::displayGraph() const {
    for (const auto& node : graph) {
        cout << "\nNode " << node.first << " ->";
        for (const auto& neighbor : node.second) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }
}
// public function to start dfs
void RouteOptimization::dfs(const std::string &startNode) const{
    unordered_set<string> visited;                                      // track visited nodes
    cout << "\nDFS starting from node " << startNode << ":" << endl;
    dfsHelper(startNode, visited);
    cout << endl;
}
// private recursive helper function for dfs
void RouteOptimization::dfsHelper(const std::string &node, unordered_set<std::string> &visited) const {
    visited.insert(node);                                           // mark current node as visited
    cout << node << " ";                                               // print current node

    // explore all neighbors
    for (const auto& neighbor : graph.at(node)) {
        if (visited.find(neighbor.first) == visited.end()) {        // if not visited
            dfsHelper(neighbor.first, visited);
        }
    }

}
// public function to perform bfs starting from a given node
void RouteOptimization::bfs(const std::string &startNode) const {
    unordered_set<string> visited;                                      // set to track visited nodes
    queue<string> q;                                                    // queue for bfs traversal

    // start bfs from initial node
    visited.insert(startNode);
    q.push(startNode);

    cout << "BFS starting from node " << startNode << ":" << endl;

    while (!q.empty()) {
        string current = q.front();                                     // dequeue the front node
        q.pop();
        cout << current << " ";                                         // print current node

        // explore neighbors
        for (const auto& neighbor : graph.at(current)) {
            if (visited.find(neighbor.first) == visited.end()) {    // if not visited
                visited.insert(neighbor.first);                     // mark as visited
                q.push(neighbor.first);                             // enqueue neighbor
            }
        }
    }
    cout << endl;
}
