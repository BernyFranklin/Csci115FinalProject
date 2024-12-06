#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"
#include "SinglyOrderList.h"

using namespace std;

int main() {
    // file contains the original sample input of 50 orders
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";

    // create the array
    ArrayOrderList orderList;
    // load current values from list
    orderList.loadFromFile(orderFile);

    // create the SinglyLinkedList
    SinglyOrderList singlyOrderList;

    // iterate through array and fill the list
    for (int i = 0; i < orderList.getSize(); i++) {
        singlyOrderList.addOrder(orderList.getOrder(i));
    }

    // display the list
    cout << "Orders in the singly linked list:" << endl;
    singlyOrderList.displayOrders();

    // test add
    singlyOrderList.addOrder(Order("ORD52", 1, "Y"));

    cout << "Updated orders:" << endl;
    singlyOrderList.displayOrders();



    return 0;
}