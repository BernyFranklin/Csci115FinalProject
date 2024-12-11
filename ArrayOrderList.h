#ifndef ARRAYORDERLIST_H
#define ARRAYORDERLIST_H
#include <string>
#include "Orders.h"

using namespace std;

const int DEFAULT_SIZE = 50;
class ArrayOrderList {
private:
    Order* orders;      // pointer to the dynamic array of orders
    int size;           // current number of orders
    int capacity;       // maximum capacity of the array
    void resize();      // resize the array when capacity is exceeded

public:
    explicit ArrayOrderList(int initialCapacity = DEFAULT_SIZE);    // constructor with default
    ~ArrayOrderList();                                              // destructor to free up memory

    // getters
    int getSize() const;                                            // gets size
    Order getOrder(int index) const;                                // gets order

    // functions being tested
    bool addOrder(const Order& order);                              // add order to list
    void removeOrder(const string& orderId);                        // removes order by orderId
    int searchByOrderId(const string& orderId) const;               // linear searchByOrderId for orderId
    void updatePriority(const string& orderId, int newPriority);    // updates priority level for an orderId

    // other functions
    void loadFromFile(const string& filename);                      // load orders
    void displayOrders() const;                                     // display all orders
    void displaySingleOrder(int index) const;                       // display single order

};
#endif