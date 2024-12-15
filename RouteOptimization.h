#ifndef ROUTEOPTIMIZATION_H
#define ROUTEOPTIMIZATION_H
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

using namespace std;

class RouteOptimization {
private:
    // adjacency list representation: Node -> list of pairs (Neighbor, Weight)
    unordered_map<string, vector<pair<string, int>>> graph;
    void dfsHelper(const string& node, unordered_set<string>& visited) const;

public:
    RouteOptimization();
    void displayGraph() const;
    void dfs(const string& startNode) const;
    void bfs(const string& startNode) const;
};
#endif