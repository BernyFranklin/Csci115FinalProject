#ifndef TIMEDOPERATIONS_H
#define TIMEDOPERATIONS_H
#include "RouteOptimization.h"
#include "BstOrderList.h"
#include "AvlOrderList.h"
#include <string>
using namespace std;
class TimedOperations {
public:
    static void timedBFS(const RouteOptimization& route, const string& startNode, const string& targetNode) ;
    static void timedDFS(const RouteOptimization& route, const string& startNode, const string& targetNode) ;
    static void timedDijkstra(const RouteOptimization& route, const string& startNode, const string& targetNode) ;
    static void timedBinarySearch(BstOrderList& bst, string& targetId);
    static void timedAvlSearch(AvlOrderList& avl, string& targetId);
};

#endif