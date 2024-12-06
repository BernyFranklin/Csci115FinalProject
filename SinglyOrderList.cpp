#include "SinglyOrderList.h"
#include <iostream>

using namespace std;

// constructor
SinglyOrderList::SinglyOrderList() : head(nullptr), size(0) {}

// destructor
SinglyOrderList::~SinglyOrderList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;                // delete each node
    }
}

// add order to list
void SinglyOrderList::addOrder(const Order &order) {
    Node* newNode = new Node(order);            // create new node
    if (!head) {
        // if empty, new node is head
        head = newNode;
    }
    else {
        // traverse to the end
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;                                     // increment the size
}

// search for an order
const Order* SinglyOrderList::searchByOrderId(const std::string &orderId) const {
    Node* current = head;                           // start at the head of the list
    while (current) {
        if (current->data.getId() == orderId) {
            return &(current->data);                // return a pointer to the found order
        }
        current = current->next;                    // move to the next node
    }
    return nullptr;                                 // return nullptr if not found
}
// display all orders in the list
void SinglyOrderList::displayOrders() const {
    Node* current = head;
    while (current) {
        current->data.displayOrder();           // Use Order's displayOrder function
        current = current->next;
    }
}