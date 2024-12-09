#include "ArrayOrderList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// constructor
ArrayOrderList::ArrayOrderList(int initialCapacity)
    : size(0), capacity(initialCapacity) {
    orders = new Order[capacity];               // allocate initial array
}

// destructor
ArrayOrderList::~ArrayOrderList() {
    delete[] orders;                            // free up memory
}

// resizes array if it's going to exceed the capacity
void ArrayOrderList::resize() {
    capacity *= 2;                              // double the capacity
    Order* newOrders = new Order[capacity];     // allocate a larger array

    // old array into new one
    for (int i = 0; i < size; i++) {
        newOrders[i] = orders[i];
    }

    delete[] orders;                            // clean up garbage
    orders = newOrders;                         // update the pointer
}

// returns how big the array is
int ArrayOrderList::getSize() const {return size;}

// retrieves order by index and returns order object
Order ArrayOrderList::getOrder(int index) const {return orders[index];}

// adds order to the array, resizes if needed
void ArrayOrderList::addOrder(const Order& order) {
    if (size >= capacity) {
        resize();                               // resize if the array is full
    }
    orders[size++] = order;                     // add order and increment size
}

// loads array from file
void ArrayOrderList::loadFromFile(const string &filename) {
    ifstream file(filename);

    // raise error if file fails to load
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // create order objects from file input
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string id, destination;
        int priority;

        // go through the line, grab the id, go past the comma and grab the priority, skip the comma and
        // grab the destination. If the line isn't formatted correctly it will skip it
        if (getline(ss, id, ',') && ss >> priority && ss.ignore() && getline(ss, destination)) {
            // create and add order
            addOrder(Order(id, priority, destination));
        }
    }

    file.close();
}

// displays all orders in array
void ArrayOrderList::displayOrders() const {
    for (int i = 0; i < size; i++) {
        orders[i].displayOrder();
    }
}

// displays a single order
void ArrayOrderList::displaySingleOrder(int index) const {
    if (index >= 0 && index < size) {
        orders[index].displayOrder();               // calls displayOrder from Orders module
    }
    else {
        cerr << "Invalid index: " << index << endl;
    }
}

// search for an order by orderId
int ArrayOrderList::searchByOrderId(const std::string &orderId) const {
    for (int i = 0; i < size; i++) {
        if (orders[i].getId() == orderId) {
            return i;
        }
    }
    return -1;
}