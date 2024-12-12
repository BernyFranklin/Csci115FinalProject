#include "OrderSorting.h"
#include <cstdlib>      // for rand
#include <ctime>        // for seeding rand
#include <sstream>      // for generating orderId in hex
#include <iomanip>

using namespace std;

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