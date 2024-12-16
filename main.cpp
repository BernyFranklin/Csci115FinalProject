#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"
#include "SinglyOrderList.h"
#include "DoublyOrderList.h"
#include "SkipOrderList.h"
#include "OrderSorting.h"
#include "BstOrderList.h"
#include "AvlOrderList.h"
#include "RouteOptimization.h"

using namespace std;

void testBinarySearch(BstOrderList& bst, string& targetId) {
    auto startTime = chrono::high_resolution_clock::now();
    bst.removeOrder(targetId);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    cout << "BST deleted order with ID " << targetId << " in " << duration << " nanoseconds." << endl;

}
void testAvlSearch(AvlOrderList& avl, string& targetId) {
    auto startTime = chrono::high_resolution_clock::now();
    avl.removeOrder(targetId);
    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    cout << "AVL deleted order with ID " << targetId << " in " << duration << " nanoseconds." << endl;

}
int main() {
    // file contains the original sample input of 50 orders
    // replace this string to match where the folder is on YOUR machine
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";

    // create the array
    ArrayOrderList arrayList;
    // load values
    arrayList.loadFromFile(orderFile);


    // create the SinglyLinkedList
    SinglyOrderList singlyList;
    // iterate through array and fill the list
    for (int i = 0; i < arrayList.getSize(); i++) {
        singlyList.addOrder(arrayList.getOrder(i));
    }

    // create DoublyOrderList
    DoublyOrderList doublyList;
    // convert our singly to the doubly
    doublyList.convertFromSingly(singlyList);

    // create SkipOrderList
    SkipOrderList skipList;
    //load skipList with the array
    skipList.loadFromArray(arrayList);

    // create BstOrderList
    BstOrderList bst;
    bst.loadFromArrayOrderList(arrayList);

    // create AvlOrderList
    AvlOrderList avl;
    avl.convertFromBst(bst);

    // create graph
    RouteOptimization route;
    cout << "Weighted Directed Graph:" << endl;
    // display graph
    route.displayGraph();
    // perform dfsAllNodes starting at node "A"
    route.dfsAllNodes("A");
    route.bfsAllNodes("A");
    route.bfsTargetNode("A", "J");
    route.dfsTargetNode("A", "J");

    return 0;
}