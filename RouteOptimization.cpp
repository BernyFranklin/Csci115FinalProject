#include "RouteOptimization.h"
#include <unordered_set>
#include <unordered_map>
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
// public function to perform dfsAllNodes
void RouteOptimization::dfsAllNodes(const string &startNode) const{
    unordered_set<string> visited;                                      // track visited nodes
    cout << "\nDFS starting from node " << startNode << ":" << endl;
    dfsAllNodesHelper(startNode, visited);
    cout << endl;
}
// public function to perform dfs to a target node
void RouteOptimization::dfsTargetNode(const std::string &startNode, const std::string &targetNode) const {
    unordered_set<string> visited;                  // track visited nodes
    vector<pair<string, int>> path;                 // tracks path weights
    int currentWeight = 0;                          // tracks accumulated weight
    bool found = dfsTargetNodeHelper(startNode, targetNode, visited, path, currentWeight);

    if (found) {
        cout << "Path (DFS) from " << startNode << " to " << targetNode << ":" << endl;
        int totalWeight = 0;
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << path[i].first << "(" << path[i].second << ")";
            totalWeight += path[i].second;
        }
        cout << "(Total Weight: " << totalWeight << ")" << endl;
        return;
    }
    cout << "Target node " << targetNode << " not reachable from " << startNode << "." << endl;
}
// private recursive helper function for dfsAllNodes
void RouteOptimization::dfsAllNodesHelper(const string &node, unordered_set<string> &visited) const {
    visited.insert(node);                                           // mark current node as visited
    cout << node << " ";                                               // print current node

    // explore all neighbors
    for (const auto& neighbor : graph.at(node)) {
        if (visited.find(neighbor.first) == visited.end()) {        // if not visited
            dfsAllNodesHelper(neighbor.first, visited);
        }
    }

}
// private recursive helper function for dfs to a target node
bool RouteOptimization::dfsTargetNodeHelper(const std::string &node, const std::string &targetNode,
                                            unordered_set<std::string> &visited, vector<pair<std::string, int>> &path,
                                            int &currentWeight) const {
    visited.insert(node);

    if (path.empty()) {
        path.push_back({node, 0});      // add starting node with weight 0
    }
    // if found
    if (node == targetNode) {
        return true;
    }

    // explore neighbors
    for (const auto& neighbor : graph.at(node)) {
        if (visited.find(neighbor.first) == visited.end()) {
            path.push_back({neighbor.first, neighbor.second});        // add current node and edge weight
            currentWeight += neighbor.second;
            if (dfsTargetNodeHelper(neighbor.first, targetNode, visited, path, currentWeight)) {
                return true;                                        // stop recursion
            }

            // backtrack
            path.pop_back();
            currentWeight -= neighbor.second;
        }
    }
    return false;
}
// public function to perform bfsAllNodes starting from a given node
void RouteOptimization::bfsAllNodes(const string &startNode) const {
    unordered_set<string> visited;                                      // set to track visited nodes
    queue<string> q;                                                    // queue for bfsAllNodes traversal

    // start bfsAllNodes from initial node
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
// public function to perform bfs to a target node from a given starting node
void RouteOptimization::bfsTargetNode(const std::string &startNode, const std::string &targetNode) const {
    unordered_set<string> visited;                      // track visited nodes
    unordered_map<string, pair<string, int>> parent;    // track parent and edge weight
    queue<string> q;                                    // queue for bfs
    unordered_map<string, int> totalWeight;             // tracks total weight

    visited.insert(startNode);
    q.push(startNode);
    totalWeight[startNode] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        // check if we reached the target
        if (current == targetNode) {
            // backtrack and print the path
            vector<string> path;
            int weight = totalWeight[targetNode];
            string node = targetNode;

            while (node != startNode) {
                auto& prev = parent[node];
                path.push_back(node + "(" + to_string(prev.second) + ")");
                node = prev.first;
            }
            path.push_back(startNode);
            reverse(path.begin(), path.end());

            cout << "Shortest path (BFS) from " << startNode << " to " << targetNode << ":" << endl;
            for (size_t i = 0; i < path.size(); i++) {
                if (i > 0) cout << " -> ";
                cout << path [i];
            }
            cout << " (Total Weight: " << weight << ")" << endl;
            return;
        }

        // explore neighbors
        for (const auto& neighbor : graph.at(current)) {
            if (visited.find(neighbor.first) == visited.end()) {
                visited.insert(neighbor.first);
                q.push(neighbor.first);
                parent[neighbor.first] = {current, neighbor.second};    // record parent and weight
                totalWeight[neighbor.first] = totalWeight[current] + neighbor.second;
            }
        }
    }

    // if not found
    cerr << "Error: Target Node " << targetNode << " not reachable from " << startNode << "." << endl;
}
