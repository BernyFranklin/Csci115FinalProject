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
    // test of adding a new order
    orderList.addOrder(Order("ORD51", 3, "Z"));

    // create the SinglyLinkedList
    SinglyOrderList singlyOrderList;

    // iterate through array and fill the list
    for (int i = 0; i < orderList.getSize(); i++) {
        singlyOrderList.addOrder(orderList.getOrder(i));
    }

    // display the list
    cout << "Orders in the singly linked list:" << endl;
    singlyOrderList.displayOrders();



    return 0;
}