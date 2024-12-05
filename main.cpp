#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"

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
    // test of search
    string searchId = "ORD70";
    int index = orderList.searchByOrderId(searchId);

    if (index != -1) {
        orderList.displaySingleOrder(index);
    }
    else {
        cout << "Order with ID " << searchId << " not found." << endl;
    }

    return 0;
}