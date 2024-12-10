#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"
#include "SinglyOrderList.h"
#include "DoublyOrderList.h"
#include "SkipOrderList.h"

using namespace std;


int main() {
    // file contains the original sample input of 50 orders
    // replace this string to match where the folder is on YOUR machine
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";

    // create the array
    ArrayOrderList arrayList;
    // load current values from text file
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
    // load skipList with the array
    skipList.loadFromArray(arrayList);
    skipList.updatePriority("ORD50", 1);
    Order orderInquiry = skipList.getOrder("ORD50");
    orderInquiry.displayOrder();


    return 0;
}