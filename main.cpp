#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"
#include "SinglyOrderList.h"
#include "DoublyOrderList.h"
#include "SkipOrderList.h"
#include "OrderSorting.h"
#include "BstOrderList.h"

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
    //OrderSorting::generateOrders(1000, arrayList);
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
    SkipOrderList skipList;
    // load skipList with the array
    skipList.loadFromArray(arrayList);
    */

    BstOrderList bst;
    bst.loadFromArrayOrderList(arrayList);
    bst.exportTree("/Users/frankbernal/CLionProjects/Csci115FinalProject/bst_tree.dot");
    return 0;
}