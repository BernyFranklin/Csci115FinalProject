#include "RouteOptimization.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <limits>

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
    int finalWeight = 0;                          // tracks accumulated weight
    bool found = dfsTargetNodeHelper(startNode, targetNode, visited, path, 0, finalWeight);

    if (found) {
        cout << "Path (DFS) from " << startNode << " to " << targetNode << ":" << endl;
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) cout << " -> ";
            cout << path[i].first << "(" << path[i].second << ")";
        }
        cout << "(Total Weight: " << finalWeight << ")" << endl;
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
                                            int currentWeight, int& finalWeight) const {
    visited.insert(node);

    if (path.empty()) {
        path.push_back({node, 0});      // add starting node with weight 0
    }
    // if found
    if (node == targetNode) {
        finalWeight = currentWeight;
        return true;
    }

    // explore neighbors
    for (const auto& neighbor : graph.at(node)) {
        if (visited.find(neighbor.first) == visited.end()) {
            path.push_back({neighbor.first, neighbor.second});        // add current node and edge weight

            if (dfsTargetNodeHelper(neighbor.first, targetNode, visited, path, currentWeight + neighbor.second, finalWeight)) {
                return true;                                        // stop recursion
            }

            // backtrack
            path.pop_back();
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
// custom comparator for priority queue for Dijkstra
struct Compare {
    bool operator()(const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;           // min-heap based on distance
    }
};
// dijkstra's algorithm to find shortest paths from a start node
void RouteOptimization::dijkstraAllNodes(const std::string &startNode) const {
    priority_queue<pair<int, string>, vector<pair<int, string>>, Compare> pq;
    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    // initialize distances to infinity and parent nodes to empty
    for (const auto& pair : graph) {
        distance[pair.first] = numeric_limits<int>::max();
    }

    // distance to the start node is 0
    distance[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        // if current distance is greater, skip processing
        if (currentDist > distance[currentNode]) continue;

        // explore neighbors
        for (const auto& neighbor : graph.at(currentNode)) {
            const string& neighborNode = neighbor.first;
            int edgeWeight = neighbor.second;

            // calculate new distance
            int newDist = distance[currentNode] + edgeWeight;

            // update distance if it's shorter
            if (newDist < distance[neighborNode]) {
                distance[neighborNode] = newDist;
                parent[neighborNode] = currentNode;
                pq.push({newDist, neighborNode});
            }
        }
    }

    // display results
    cout << "Shortest paths from node " << startNode << ":" << endl;
    for (const auto& pair : distance) {
        string node = pair.first;
        int dist = pair.second;

        if (dist == numeric_limits<int>::max()) {
            cout << node << ": Unreachable" << endl;
        }
        else {
            // reconstruct path
            string path = node;
            string current = node;
            while (parent.find(current) != parent.end()) {
                current = parent[current];
                path = current + " -> " + path;
            }
            cout << node << ": " << dist << " (Path: " << path << ")" << endl;
        }
    }
}
// dijkstra's algorithm to find shortest path to a target node
bool RouteOptimization::dijkstraTargetNode(const std::string &startNode, const std::string &targetNode) const {
    priority_queue<pair<int, string>, vector<pair<int, string>>, Compare> pq;
    unordered_map<string, int> distance;            // to store shortest distance
    unordered_map<string, string> parent;           // to reconstruct path

    // initialize distances to infinity
    for (const auto& pair : graph) {
        distance[pair.first] = numeric_limits<int>::max();
    }

    // start node distance is 0
    distance[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        // if we reached the target node, reconstruct and display path
        if (currentNode == targetNode) {
            cout << "Shortest path to node " << targetNode << ":" << endl;
            string path = targetNode;
            string current = targetNode;
            int totalWeight = distance[targetNode];

            // reconstruct path
            while (parent.find(current) != parent.end()) {
                current = parent[current];
                path = current + " -> " + path;
            }

            cout << path << " (Total Weight: " << totalWeight << ")" << endl;
            return true;
        }
        // skip if this distance is no longer optimal
        if (currentDist > distance[currentNode]) continue;

        // explore neighbors
        for (const auto& neighbor : graph.at(currentNode)) {
            const string& neighborNode = neighbor.first;
            int edgeWeight = neighbor.second;

            // calculate new distance
            int newDist = distance[currentNode] + edgeWeight;

            // if this path is shorter, update the distance and parent
            if (newDist < distance[neighborNode]) {
                distance[neighborNode] = newDist;
                parent[neighborNode] = currentNode;
                pq.push({newDist, neighborNode});
            }
        }
    }
    // target node not reachable
    cout << "Target node " << targetNode << " is not reachable from " << startNode << "." << endl;
    return false;
}
