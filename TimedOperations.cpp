#include "TimedOperations.h"
#include "RouteOptimization.h"
#include <chrono>
#include <string>

void TimedOperations::timedBFS(const RouteOptimization& route, const string &startNode, const string &targetNode) {
    auto startTime = chrono::high_resolution_clock::now();
    route.bfsTargetNode(startNode, targetNode);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "Completed in " << duration << " microseconds.\n\n";
}

void TimedOperations::timedDFS(const RouteOptimization &route, const string &startNode, const string &targetNode) {
    auto startTime = chrono::high_resolution_clock::now();
    route.dfsTargetNode(startNode, targetNode);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "Completed in " << duration << " microseconds.\n\n";
}

void TimedOperations::timedDijkstra(const RouteOptimization &route, const std::string &startNode,
                                    const std::string &targetNode) {
    auto startTime = chrono::high_resolution_clock::now();
    route.dijkstraTargetNode(startNode, targetNode);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "Completed in " << duration << " microseconds.\n\n";
}