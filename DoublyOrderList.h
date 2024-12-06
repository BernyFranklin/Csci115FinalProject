#ifndef DOUBLY_ORDER_LIST_H
#define DOUBLY_ORDER_LIST_H
#include "Orders.h"
#include "SinglyOrderList.h"

class DoublyOrderList {
private:
    struct Node {
        Order data;     // order object as data
        Node* next;     // pointer to next node
        Node* prev;     // pointer to previous node

        // node constructor
        Node(const Order& order, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : data(order), next(nextNode), prev(prevNode) {}
    };

    Node* head;         // pointer to the head of the list
    Node* tail;         // pointer to the tail of the list
    int size;           // number of nodes in the list

public:
    DoublyOrderList();      // constructor
    ~DoublyOrderList();     // destructor

    void addOrder(const Order& order);                              // adds order to end of list
    bool removeOrder(const string& orderId);                        // removes order from list
    void displayForward() const;                                    // display orders forward
    void displayBackward() const;                                   // display orders backward
    void convertFromSingly(const SinglyOrderList& singlyList);      // convert singly to doubly
};
#endif