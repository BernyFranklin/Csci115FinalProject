#include "SkipOrderList.h"
#include <iostream>
#include<iomanip>

using namespace std;

// constructor
SkipOrderList::SkipOrderList(int maxLevel)
    : maxLevel(maxLevel), currentLevel(0) {
    // initialize the head node with the maximum level
    head = new Node(Order("", 0, ""), maxLevel);
    srand(time(nullptr));
}

// destructor
SkipOrderList::~SkipOrderList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next[0];                          // move to the next node
        delete temp;
    }
}

// functions
// generate a random level for a new node
int SkipOrderList::randomLevel() {
    int level = 1;
    while(rand() % 2 == 0 && level < maxLevel) {
        level++;                                            // increment level with a 50/50 chance
    }
    return level;
}

// load list from an array
void SkipOrderList::loadFromArray(const ArrayOrderList& arrayList) {
    // iterate through the elements of the array
    for (int i = 0; i < arrayList.getSize(); i++) {
        const Order& order = arrayList.getOrder(i);     // retrieve the order from the array
        addOrder(order);                                        // addOrder order into skip list
    }
}

// addOrder an order into the skip list
void SkipOrderList::addOrder(const Order& order) {
    vector<Node*> update(maxLevel, nullptr);         // track nodes to update
    Node* current = head;

    // traverse from the top level to level 0
    for (int i = currentLevel; i >= 0; i--) {
        while (current->next[i] && current->next[i]->data.getId() < order.getId()) {
            current = current->next[i];                     // move forward at the current level
        }
        update[i] = current;                                // store the last node at this level
    }

    // determine the level for the new node
    int level = randomLevel();

    // if the new level is higher than the current level, update head
    if (level > currentLevel) {
        for (int i = currentLevel + 1; i < level; i++) {
            update[i] = head;
        }
        currentLevel = level - 1;
    }

    //create the new node
    Node* newNode = new Node(order, level);

    // update pointers at each level
    for (int i = 0; i < level; i++) {
        newNode->next[i] = update[i]->next[i];
        update[i]->next[i] = newNode;
    }
}

// delete an order by orderId
void SkipOrderList::removeOrder(const string &orderId) {
    vector<Node*> update(maxLevel, nullptr);            // track nodes to update
    Node* current = head;

    // traverse the list to find the node and prepare to update pointers
    for (int i = currentLevel; i >= 0; i--) {
        while (current->next[i] && current->next[i]->data.getId() < orderId) {
            current = current->next[i];
        }
        update[i] = current;                                  // store the node at this level
    }

    // move to the next node at level 0;
    current = current->next[0];

    // check if the node to delete exists
    if (!current || current->data.getId() != orderId) {
        cerr << "Order with ID " << orderId << " not found." << endl;
    }

    // update pointers to bypass the node being deleted
    for (int i = 0; i <= currentLevel; i++ ) {
        if (update[i]->next[i] == current) {
            update[i]->next[i] = current->next[i];
        }
    }

    // adjust the current level if needed
    while (currentLevel > 0 && head->next[currentLevel] == nullptr) {
        currentLevel--;
    }

    delete current;                                             // free memory
    cout << "Order with ID " << orderId << " deleted successfully." << endl;
}

// searchByOrderId by orderId
SkipOrderList::Node *SkipOrderList::searchByOrderId(const string &orderId) const {
    Node* current = head;

    // traverse the levels from the top to bottom
    for (int i = currentLevel; i >= 0; i--) {
        while (current->next[i] && current->next[i]->data.getId() < orderId) {
            current = current->next[i];         // move forward in the current level
        }
    }

    // move to the next node at the lowest level
    current = current->next[0];

    // check if the orderId matches
    if (current && current->data.getId() == orderId) {
        cout << "Order found: " << endl;
        current->data.displayOrder();                  // return the found order
        return current;
    }
    else{
        // if not found, print error and return an empty order
        cerr << "Order with ID " << orderId << " not found." << endl;
    }

    return nullptr;                     // if not found return null
}

// update priority by orderId
void SkipOrderList::updatePriority(const std::string &orderId, int newPriority) {
    // validate range
    if (newPriority < 1 || newPriority > 5) {
        cerr << "Error: priority must be between 1 and 5." << endl;
        return;
    }

    // traverse levels from top to bottom to find order
    Node* current = head;
    for (int i = currentLevel; i >= 0; i--) {
        while (current->next[i] && current->next[i]->data.getId() < orderId) {
            current = current->next[i];             // move forward at the current level
        }
    }

    // move to the next node at the lowest level
    current = current->next[0];

    // check if node with given orderId exists
    if (!current || current->data.getId() != orderId) {
        cerr << "Error: Order with ID " << orderId << " not found." << endl;
        return;
    }

    // update priority
    current->data.setPriority(newPriority);
    cout << "Priority of Order with ID " << orderId << " updated to " << newPriority << "." << endl;
}

// display the skip list
void SkipOrderList::display() const {
    for (int i = currentLevel; i >= 0; i--){
        Node* current = head->next[i];
        cout << "Level " << i << ": ";
        while (current) {
            cout << "[" << current->data.getId() << "] ";
            current = current->next[i];
        }
        cout << endl;
    }
}