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
        insert(order);                                        // insert order into skip list
    }
}
// insert an order into the skip list
void SkipOrderList::insert(const Order& order) {
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

// display the skip list
void SkipOrderList::display() const {
    for (int i = currentLevel; i >= 0; i--){
        Node* current = head->next[i];
        cout << "Level " << i << ": ";
        while (current) {
            cout << "[" << current->data.getId() << "} ";
            current = current->next[i];
        }
        cout << endl;
    }
}