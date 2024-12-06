#include "DoublyOrderList.h"
#include <iostream>

using namespace std;

// constructor
DoublyOrderList::DoublyOrderList() : head(nullptr), tail(nullptr), size(0) {}

// destructor
DoublyOrderList::~DoublyOrderList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// search for an orderId
DoublyOrderList::Node* DoublyOrderList::searchById(const std::string &orderId) const {
    Node* current = head;               // start at the head
    while (current) {
        if (current->data.getId() == orderId) {
            return current;             // return the pointer if found
        }
        current = current->next;
    }
    return nullptr;                     // not found
}
// add order to end of list
void DoublyOrderList::addOrder(const Order &order) {
    Node* newNode = new Node(order);

    if(!head) {
        head = tail = newNode;          // first node
    }
    else {
        tail->next = newNode;           // link new node to tail
        newNode->prev = tail;           // new node points to previous
        tail = newNode;                 // new node is the tail
    }
    size++;                             // increase the size of the list
}

bool DoublyOrderList::removeOrder(const std::string &orderId) {
    Node* targetNode = searchById(orderId);

    // Node found, handle diff cases
    if (targetNode == head && targetNode == tail) {
        // single node in list
        head = tail = nullptr;
    }
    else if (targetNode == head) {
        // remove the head!
        head = head->next;
        head->prev = nullptr;
    }
    else if (targetNode == tail) {
        // cut off the tail
        tail = tail->prev;
        tail->next = nullptr;
    }
    else {
        // remove any other node
        targetNode->prev->next = targetNode->next;
        targetNode->next->prev = targetNode->prev;
    }

    delete targetNode;          // free memory
    size--;                     // reduce size
    return true;
}

// display orders --This Way-->
void DoublyOrderList::displayForward() const {
    Node* current = head;
    while (current) {
        current->data.displayOrder();
        current = current->next;
    }
}

// display orders <--This Way--
void DoublyOrderList::displayBackward() const {
    Node* current = tail;
    while (current) {
        current->data.displayOrder();
        current = current->prev;
    }
}

// make the one way list go BOTH ways
void DoublyOrderList::convertFromSingly(const SinglyOrderList &singlyList) {
    // Start at the head of the singly
    const SinglyOrderList::Node* current = singlyList.getHead();
    while (current) {
        addOrder(current->data);        // add each order to the double linked list
        current = current->next;              // move to next node
    }
}