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
#include "UserInterface.h"
#include "TimedOperations.h"

using namespace std;

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

    char userInput = 'x';
    while(userInput != '0') {
        UserInterface::displayMenu();
        userInput = UserInterface::getInput();
    }
    cout << "Thank you for using the app!" << endl;


    return 0;
}