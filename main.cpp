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
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";

    // create the array
    ArrayOrderList arrayList;
    // load current values from list
    arrayList.loadFromFile(orderFile);

    // create the SinglyLinkedList
    SinglyOrderList singlyList;

    // iterate through array and fill the list
    for (int i = 0; i < arrayList.getSize(); i++) {
        singlyList.addOrder(arrayList.getOrder(i));
    }

    // create DoublyOrderList
    DoublyOrderList doublyList;
    doublyList.convertFromSingly(singlyList);
    doublyList.displayForward();

    // create SkipOrderList
    SkipOrderList skipList;
    skipList.loadFromArray(arrayList);
    skipList.insert(Order("ORD75", 3, "X"));
    skipList.display();
    skipList.search("ORD85");
    skipList.deleteOrder("ORD02");
    skipList.display();
    return 0;
}