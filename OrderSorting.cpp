#include "OrderSorting.h"
#include <cstdlib>      // for rand
#include <ctime>        // for seeding rand
#include <sstream>      // for generating orderId in hex
#include <iomanip>      // for formatting
#include <iostream>     // for stuff

using namespace std;

// generates N Order objects and stores them in an ArrayOrderList
void OrderSorting::generateOrders(int n, ArrayOrderList& list) {
    srand(time(nullptr));       // seed the random number generator

    char destination = 'A';     // start with 'A' for the destination

    // create N orders
    for (int i = 1; i <= n; i++) {
        //generate orderId in hex
        stringstream ss;
        ss << "ORD" << hex << uppercase << setw(4) << setfill('0') << i;
        // set to string
        string orderId = ss.str();

        // generate a random priority
        int priority = (rand() % 5) + 1;

        // create the Order object and add it to the list
        list.addOrder(Order(orderId, priority, string(1, destination)));

        // increment destination, cycling through A-Z
        destination = (destination == 'Z') ? 'A' : destination + 1;
    }
}

// performs selection sort of ArrayOrderList and sorts by priority
void OrderSorting::selectionSort(ArrayOrderList &list) {
    int n = list.getSize();     // gets number of elements in array

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        // find index of the smallest element in the unsorted part
        for (int j = i + 1; j < n; j++) {
            if (list.getOrder(j).getPriority() < list.getOrder(minIndex).getPriority())
                minIndex = j;
        }

        // swap the current element with the smallest element found
        if (minIndex != i) {
            Order temp = list.getOrder(i);                              // access array directly
            list.setOrder(i, list.getOrder(minIndex));     // first swap
            list.setOrder(minIndex, temp);                       // second swap
        }
    }

    // alert user
    cout << "\n\nOrders sorted by priority in ascending order." << endl;
}

