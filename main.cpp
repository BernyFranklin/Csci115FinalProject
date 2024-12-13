#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"
#include "SinglyOrderList.h"
#include "DoublyOrderList.h"
#include "SkipOrderList.h"
#include "OrderSorting.h"

using namespace std;


int main() {
    // file contains the original sample input of 50 orders
    // replace this string to match where the folder is on YOUR machine
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";

    // create the array
    //ArrayOrderList arrayList;
    // load values
    //arrayList.loadFromFile(orderFile);
    for (int i = 0; i < 10; i++) {
        cout << "\nIteration " << i + 1;
        ArrayOrderList arrayList;
        OrderSorting::generateOrders(10'000, arrayList);
        OrderSorting::timedSort(OrderSorting::quickSort, arrayList);
    }

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
    return 0;
}