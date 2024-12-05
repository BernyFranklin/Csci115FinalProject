#include "ArrayOrderList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

ArrayOrderList::ArrayOrderList(int initialCapacity)
    : size(0), capacity(initialCapacity) {
    orders = new Order[capacity];               // allocate initial array
}

ArrayOrderList::~ArrayOrderList() {
    delete[] orders;                            // free up memory
}

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

void ArrayOrderList::addOrder(const Order& order) {
    if (size >= capacity) {
        resize();                               // resize if the array is full
    }
    orders[size++] = order;                     // add order and increment size
}

void ArrayOrderList::loadFromFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string id, destination;
        int priority;

        if (getline(ss, id, ',') && ss >> priority && ss.ignore() && getline(ss, destination)) {
            // create and add order
            addOrder(Order(id, priority, destination));
        }
    }

    file.close();
}

void ArrayOrderList::displayOrders() const {
    for (int i = 0; i < size; i++) {
        orders[i].displayOrder();
    }
}

int ArrayOrderList::searchByOrderId(const std::string &orderId) const {
    for (int i = 0; i < size; i++) {
        if (orders[i].getId() == orderId) {
            return i;
        }
    }
    return -1;
}