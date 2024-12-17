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
            if (order.getId() == current->data.getId()) {
                cerr << "\n\nError: Order with ID " << order.getId() << " already exists." << endl;
                return;
            }
            current = current->next;
        }
        current->next = newNode;
    }
    size++;                                     // increment the size
}

// remove order by orderId
void SinglyOrderList::removeOrder(const std::string &orderId) {
    string successString = "\n\nOrder with ID " + orderId + " removed successfully.\n";
    // empty list case
    if (!head) {
        cerr << "Error: the list is empty." << endl;
        return;
    }

    // use searchByOrderId
    Node* targetNode = searchByOrderId(orderId);
    // not found
    if (!targetNode) {
        cerr << "\n\nError: Order with ID " << orderId << " not found" << endl;
        return;
    }
    // remove the head case
    if (head->data.getId() == orderId) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // get previous node to update pointers (since this is a singly linked list
    Node* current = head;
    while (current->next != targetNode) {
        current = current->next;
    }

    // update pointers
    current->next = targetNode->next;

    // delete node
    delete targetNode;
    size--;
    cout << successString;
}

// update priority by orderId
void SinglyOrderList::updatePriority(const std::string &orderId, int newPriority) const {
    // validate priority range
    if (newPriority < 1 || newPriority > 5) {
        cerr << "\n\nError: priority must be between 1 and 5" << endl;
        return;
    }

    // use searchByOrderId to find the target node
    Node* targetNode = searchByOrderId(orderId);
    // if not found
    if (!targetNode) {
        cerr << "\n\nError: Order with ID " << orderId << " not found." << endl;
        return;
    }

    // update the priority
    targetNode->data.setPriority(newPriority);
    cout << "\n\nPriority of Order with ID " << orderId << " updated to " << newPriority << "." << endl;
}

// searchByOrderId for an order
SinglyOrderList::Node *SinglyOrderList::searchByOrderId(const std::string &orderId) const {
    Node* current = head;                           // start at the head of the list
    while (current) {
        if (current->data.getId() == orderId) {
            return current;                         // return a pointer to the found order
        }
        current = current->next;                    // move to the next node
    }
    return nullptr;                                 // return nullptr if not found
}

// display all orders in the list
void SinglyOrderList::displayOrders() const {
    Node* current = head;
    while (current) {
        current->data.displayOrder();               // Use Order's displayOrder function
        current = current->next;
    }
}