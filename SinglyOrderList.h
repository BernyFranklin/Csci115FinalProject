#ifndef SINGLY_ORDER_LIST_H
#define SINGLY_ORDER_LIST_H
#include "Orders.h"

class SinglyOrderList {
private:
    struct Node {
        Order data;         // order object as node data for simplicity
        Node* next;         // pointer to the next node

        // node constructor
        Node(const Order& order, Node* nextNode = nullptr)
            : data(order), next(nextNode) {}
    };

    Node* head;             // pointer to the head of the list
    int size;               // number of nodes on the list

public:
    SinglyOrderList();      // constructor
    ~SinglyOrderList();     // destructor

    void addOrder(const Order& order);                                  // add order to the list
    const Order* searchByOrderId(const string& orderId) const;          // search function
    void displayOrders() const;                                         // display all orders in the list
};

#endif