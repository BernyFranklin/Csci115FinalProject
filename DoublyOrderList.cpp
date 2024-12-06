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
    Node* current = head;

    // traverse the list to find the node
    while(current) {
        if (current->data.getId() == orderId) {
            // node found
            // check if head
            if (current->prev) {
                // not the head
                current->prev->next = current->next;        // previous node now points to new neighbor
            }
            else {
                // is the head
                head = current->next;                       // behind the head is another head
            }
            // check if tail
            if (current->next) {
                //not the tail
                current->next->prev = current->prev;        // next node points to new neighbor
            }
            else {
                // is the tail
                tail = current->prev;                       // cut the tail to reveal another tail... like a lizard
            }

            delete current;                                 // free up memory
            size--;                                         // decrease size of list
            return true;                                    // we deleted it!
        }
        current = current->next;                            // move to the next node
    }

    return false;                                           // we didn't find the node
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