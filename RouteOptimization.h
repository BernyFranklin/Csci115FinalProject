#ifndef ROUTEOPTIMIZATION_H
#define ROUTEOPTIMIZATION_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class RouteOptimization {
private:
    // adjacency list representation: Node -> list of pairs (Neighbor, Weight)
    unordered_map<string, vector<pair<string, int>>> graph;

public:
    RouteOptimization();
    void displayGraph() const;
};
#endif