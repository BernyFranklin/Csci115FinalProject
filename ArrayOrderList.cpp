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

// sets an index to a specific order
void ArrayOrderList::setOrder(int index, const Order &order) {
    if (index < 0 || index >= size) {
        cerr << "\n\nError: index is out of bounds." << endl;
        return;
    }
    orders[index] = order;
}

// adds order to the array, resizes if needed
bool ArrayOrderList::addOrder(const Order& order) {
    if (size >= capacity) {
        resize();                               // resize if the array is full
    }

    for (int i = 0; i < size; i++) {
        if (order.getId() == orders[i].getId()) {
            return false;
        }
    }

    orders[size++] = order;                     // add order and increment size
    return true;
}

// removes order by orderId
void ArrayOrderList::removeOrder(const std::string &orderId) {
    int index = -1;

    // find the index of the order to be removed
    for (int i = 0; i < size; i++) {
        if (orders[i].getId() == orderId) {
            index = i;
            break;
        }
    }

    // not found
    if (index == -1) {
        cerr << "Error: order with ID " << orderId << " not found." << endl;
        return;
    }

    // shift elements to the left to fill the gap
    for (int i = index; i < size - 1; i++) {
        orders[i] = orders[i+1];
    }

    // decrease size
    size--;

    // tell user
    cout << "\n\nOrder with ID " << orderId << " removed successfully" << endl;
}

// searchByOrderId for an order by orderId
int ArrayOrderList::searchByOrderId(const std::string &orderId) const {
    for (int i = 0; i < size; i++) {
        if (orders[i].getId() == orderId) {
            cout << "\n\nOrder with ID " << orderId << " found." << endl;
            orders[i].displayOrder();
            return i;
        }
    }
    cerr << "\n\nError: Order with ID " << orderId << " not found." << endl;
    return -1;
}

// update priority level
void ArrayOrderList::updatePriority(const std::string &orderId, int newPriority) {
    // validate range
    if (newPriority < 1 || newPriority > 5) {
        cerr << "Error: Priority must be between 1 and 5." << endl;
        return;
    }

    // find the order
    int searchIndex = -1;
    searchIndex = searchByOrderId(orderId);

    // not found
    if (searchIndex == -1) {
        return;
    }
    else{
        // found, update priority
        orders[searchIndex].setPriority(newPriority);
        cout << "\n\nPriority of Order with ID " << orderId << " updated to " << newPriority << "." << endl;
    }
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

