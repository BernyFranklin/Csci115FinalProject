#include "DoublyOrderList.h"
#include <iostream>

using namespace std;

const int PRIORITY_MAX = 5;
const int PRIORITY_MIN = 1;

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

void DoublyOrderList::removeOrder(const std::string &orderId) {
    Node* targetNode = searchByOrderId(orderId);
    // node not found
    if (!targetNode) return;

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
    cout << "\n\nOrder with ID " << orderId << " deleted successfully." << endl;
    size--;                     // reduce size
}

// searchByOrderId for an orderId
DoublyOrderList::Node* DoublyOrderList::searchByOrderId(const string &orderId) const {
    Node* current = head;               // start at the head
    while (current) {
        if (current->data.getId() == orderId) {
            return current;             // return the pointer if found
        }
        current = current->next;
    }

    // not found
    cerr << "\n\nError: Order with ID " << orderId << " not found." << endl;
    return nullptr;                     // not found
}

// update priority levels
void DoublyOrderList::updatePriority(const std::string &orderId, int newPriority) {
    // make sure the priority level is valid
    if (newPriority < PRIORITY_MIN || newPriority > PRIORITY_MAX) {
        cerr << "Error: Priority must be between 1 and 5." << endl;
        return;
    }

    // searchByOrderId for the node
    Node* targetNode = searchByOrderId(orderId);

    // if not found
    if (!targetNode) return;

    // if found
    targetNode->data.setPriority(newPriority);
    cout << "\n\nPriority of " << orderId << " updated to level " << newPriority << endl;
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