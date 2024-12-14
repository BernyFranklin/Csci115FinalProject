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

using namespace std;


int main() {
    // file contains the original sample input of 50 orders
    // replace this string to match where the folder is on YOUR machine
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";

    // create the array
    ArrayOrderList arrayList;
    // load values
    arrayList.loadFromFile(orderFile);

    //ArrayOrderList arrayList;

    //OrderSorting::timedSort(OrderSorting::mergeSort, arrayList);


    /*
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
    //SkipOrderList skipList;
    //load skipList with the array
    skipList.loadFromArray(arrayList);
    */

    BstOrderList bst;
    auto startBst = chrono::high_resolution_clock::now();
    bst.loadFromArrayOrderList(arrayList);
    auto endBst = chrono::high_resolution_clock::now();
    auto durationBst = chrono::duration_cast<chrono::microseconds>(endBst-startBst).count();
    AvlOrderList avl;
    auto startAvl = chrono::high_resolution_clock::now();
    avl.convertFromBst(bst);
    auto endAvl = chrono::high_resolution_clock::now();
    auto durationAvl = chrono::duration_cast<chrono::microseconds>(endAvl-startAvl).count();
    cout << "BST built in " << durationBst << " microseconds." << endl
         << "AVL built in " << durationAvl << " microseconds." << endl;
    string targetId = "ORD40";
    startBst = chrono::high_resolution_clock::now();
    Order* temp = bst.searchByOrderId(targetId);
    endBst = chrono::high_resolution_clock::now();
    startAvl = chrono::high_resolution_clock::now();
    temp = avl.searchByOrderId(targetId);
    endAvl = chrono::high_resolution_clock::now();
    durationBst = chrono::duration_cast<chrono::nanoseconds>(endBst-startBst).count();
    durationAvl = chrono::duration_cast<chrono::nanoseconds>(endAvl-startAvl).count();
    cout << "Order with ID " << targetId << " found:" << endl
         << "Binary Search Tree search time: " << durationBst << " nanoseconds." << endl
         << "AVL Tree Search Time: " << durationAvl << " nanoseconds." << endl;



    return 0;
}