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
    void dfsAllNodesHelper(const string &node, unordered_set<string> &visited) const;
    bool dfsTargetNodeHelper(const string& node, const string& targetNode,
                             unordered_set<string>& visited, vector<pair<string,
                             int>>& path, int currentWeight, int& finalWeight) const;

public:
    RouteOptimization();
    void displayGraph() const;
    void dfsAllNodes(const string &startNode) const;
    void dfsTargetNode(const string& startNode, const string& targetNode) const;
    void bfsAllNodes(const string &startNode) const;
    void bfsTargetNode(const string& startNode, const string& targetNode) const;
    void dijkstraAllNodes(const string& startNode) const;
    bool dijkstraTargetNode(const string& startNode, const string& targetNode) const;

};

#endif