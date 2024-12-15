#include "RouteOptimization.h"

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