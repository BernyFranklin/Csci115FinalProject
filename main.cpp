/*
 * Thanks for a great semester Professor Carrasco,
 * I look forward to checking out the lab sometime soon.
 *
 * The main program keeps all the data structures intact and updates all of them during runtime,
 * while unnecessary, since we implemented them, I kept them.
 * I changed the orderId numbering system to be ORDxxxx, and the xxxx's are sequential in hex
 * I also changed the locations to B-J, that way the hub is location A, and every order
 * route can be traced.
 * The user interface is self-explanatory and easy to use.
 * Enjoy
 */

#include <iostream>
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

using namespace std;

int main() {
    // orders to create, feel free to fill with 1-65,535 orders
    // 1000 still seems instant on my machine
    int n = 1000;
    // create the array
    ArrayOrderList arrayList;
    // load values
    OrderSorting::generateOrders(n, arrayList);

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

    // initialize userInput and loop variable
    char userInput;
    bool userQuit = false;

    // start program
    while(!userQuit) {
        // extra blank space for clarity
        cout << endl;

        // main menu
        UserInterface::displayMenu();
        userInput = UserInterface::getInput();
        cout << endl;
        // userInput
        switch(userInput) {
            case '1': {
                cout << "View Order Listings Ascending" << endl;
                singlyList.displayOrders();
            }
                break;
            case '2': {
                cout << "View Order Listings Descending" << endl;
                doublyList.displayBackward();
            }
                break;
            case '3': {
                cout << "Add Order" << endl;
                string ordId = UserInterface::generateOrderId(arrayList);
                Order newOrder = UserInterface::addOrder(ordId);
                arrayList.addOrder(newOrder);
                singlyList.addOrder(newOrder);
                doublyList.addOrder(newOrder);
                skipList.addOrder(newOrder);
                bst.addOrder(newOrder);
                avl.addOrder(newOrder);
                cout << "\nOrder with ID " << ordId << " added" << endl;
                newOrder.displayOrder();
                cout << "\n";
            }
                break;
            case '4': {
                cout << "Delete Order" << endl;
                string orderId = UserInterface::getOrderId();
                bool found = avl.searchByOrderId(orderId);
                if (found) {
                    arrayList.removeOrder(orderId);
                    singlyList.removeOrder(orderId);
                    doublyList.removeOrder(orderId);
                    skipList.removeOrder(orderId);
                    bst.removeOrder(orderId);
                    avl.removeOrder(orderId);
                    cout << "\nOrder with ID " + orderId + " removed successfully.\n";
                } else {
                    cout << "Order not found" << endl;
                }
            }
                break;
            case '5': {
                cout << "Find Order by Order ID" << endl;
                    string orderId = UserInterface::getOrderId();
                    Order *targetOrder = avl.searchByOrderId(orderId);
                    if (!targetOrder) {
                        cout << "\nOrder not found" << endl;
                    } else {
                        cout << "\nOrder found" << endl;
                        targetOrder->displayOrder();
                        cout << "\n";
                    }
            }
                break;
            case '6': {
                cout << "View Route by Order ID" << endl;
                string orderId = UserInterface::getOrderId();
                Order* targetOrder = avl.searchByOrderId(orderId);
                if (!targetOrder) {
                    cout << "Order not found" << endl;
                }
                else {
                    targetOrder->displayOrder();
                    string destination = targetOrder->getDestination();
                    route.dijkstraTargetNode("A", destination);
                }
            }
                break;
            case '7': {
                cout << "Sort and View by Priority" << endl;
                // used merge sort to preserve relative order
                OrderSorting::mergeSort(arrayList);
                arrayList.displayOrders();
                cout << "\n";
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