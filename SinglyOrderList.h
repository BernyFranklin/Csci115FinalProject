#ifndef SINGLY_ORDER_LIST_H
#define SINGLY_ORDER_LIST_H
#include "Orders.h"

class SinglyOrderList {
    friend class DoublyOrderList;
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

    // getter
    const Node* getHead() const {return head;}                          // BRING ME THE HEAD >:O

    // functions being tested
    void addOrder(const Order& order);                                  // add order to the list
    void removeOrder(const string& orderId);                            // removes order by orderId
    Node *searchByOrderId(const string& orderId) const;                 // searchByOrderId function
    void updatePriority(const string& orderId, int newPriority) const;  // updates priority level by orderId

    // other functions
    void displayOrders() const;                                         // display all orders in the list
};



#endif