#include <iostream>
#include <fstream>
#include "Orders.h"
#include "ArrayOrderList.h"

using namespace std;

int main() {
    string orderFile = "/Users/frankbernal/CLionProjects/Csci115FinalProject/sampleOrders.txt";
    // create the array
    ArrayOrderList orderList;
    // load current values from list
    orderList.loadFromFile(orderFile);
    // display the loaded array
    cout << "Orders loaded from file:" << endl;
    orderList.displayOrders();
    // test of adding a new order
    orderList.addOrder(Order("ORD51", 3, "Z"));
    cout << "After adding a new order:" << endl;
    orderList.displayOrders();

    return 0;
}