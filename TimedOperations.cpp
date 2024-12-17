#include "TimedOperations.h"
#include "RouteOptimization.h"
#include "BstOrderList.h"
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

void TimedOperations::timedDijkstra(const RouteOptimization &route, const string &startNode,
                                    const std::string &targetNode) {
    auto startTime = chrono::high_resolution_clock::now();
    route.dijkstraTargetNode(startNode, targetNode);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(endTime - startTime).count();
    cout << "Completed in " << duration << " microseconds.\n\n";
}

void TimedOperations::timedBinarySearch(BstOrderList& bst, string &targetId) {
    auto startTime = chrono::high_resolution_clock::now();
    bst.removeOrder(targetId);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    cout << "BST deleted order with ID " << targetId << " in " << duration << " nanoseconds." << endl;
}

void TimedOperations::timedAvlSearch(AvlOrderList &avl, std::string &targetId) {
    auto startTime = chrono::high_resolution_clock::now();
    avl.removeOrder(targetId);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    cout << "AVL deleted order with ID " << targetId << " in " << duration << " nanoseconds." << endl;
}