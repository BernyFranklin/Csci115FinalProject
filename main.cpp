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
    bool userQuit = false;
    while(!userQuit) {
        string ordId = "ORD" + to_string(arrayList.getSize() + 1);
        UserInterface::displayMenu();
        userInput = UserInterface::getInput();
        switch(userInput) {
            case '1': {
                cout << "\nView Order Listings Ascending" << endl;
                singlyList.displayOrders();
            }
                break;
            case '2': {
                cout << "\nView Order Listings Descending" << endl;
                doublyList.displayBackward();
            }
                break;
            case '3': {
                cout << "\nAdd Order" << endl;
                Order newOrder = UserInterface::addOrder(ordId);
                arrayList.addOrder(newOrder);
                singlyList.addOrder(newOrder);
                doublyList.addOrder(newOrder);
                skipList.addOrder(newOrder);
                bst.addOrder(newOrder);
                avl.addOrder(newOrder);
                cout << "\n\nOrder with ID " << ordId << " added" << endl;
                newOrder.displayOrder();
                cout << "\n\n";
            }
                break;
            case '4': {
                cout << "\nDelete Order" << endl;
                string orderId = UserInterface::removeOrder();
                bool found = avl.searchByOrderId(orderId);
                if (found) {
                    arrayList.removeOrder(orderId);
                    singlyList.removeOrder(orderId);
                    doublyList.removeOrder(orderId);
                    skipList.removeOrder(orderId);
                    bst.removeOrder(orderId);
                    avl.removeOrder(orderId);
                }
                else {
                    cout << "\nOrder not found" << endl;
                }
            }
                break;
            case '5':
                cout << userInput << " selected" << endl;
                break;
            case '6':
                cout << userInput << " selected" << endl;
                break;
            case '7': {
                cout << "\nSort and View by Priority" << endl;
                OrderSorting::quickSort(arrayList);
                arrayList.displayOrders();
                cout << "\n\n";
            }
                break;
            default:
                userQuit = true;
                break;
        }
    }
    cout << "Thank you for using the app!" << endl;


    return 0;
}