#include "OrderSorting.h"
#include <cstdlib>      // for rand
#include <ctime>        // for seeding rand
#include <sstream>      // for generating orderId in hex
#include <iomanip>      // for formatting
#include <iostream>     // for stuff

using namespace std;

string sortedString = "\n\nOrders sorted by priority in ascending order.\n";
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
            swap(list, i , minIndex);                       // second swap
        }
    }

    // alert user
    cout << sortedString;
}

// performs bubble sort of ArrayOrderList and sorts by priority
void OrderSorting::bubbleSort(ArrayOrderList &list) {
    int n = list.getSize();

    for (int i = 0; i < n; i++) {
        bool swapped = false;       // used to terminate early
        //perform single pass of the bubble sort
        for (int j = 0; j < n - i - 1; j++) {
            if (list.getOrder(j).getPriority() > list.getOrder(j + 1).getPriority()) {
                //swap elements
                swap(list, j, j + 1);
                swapped = true;
            }
        }
        // if no swaps were made, the list is sorted
        if (!swapped) break;
    }

    // alert user
    cout << sortedString;
}

void OrderSorting::swap(ArrayOrderList& list, int index1, int index2) {
    Order temp = list.getOrder(index1);
    list.setOrder(index1, list.getOrder(index2));
    list.setOrder(index2, temp);
}

