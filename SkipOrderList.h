#ifndef SKIP_ORDER_LIST_H
#define SKIP_ORDER_LIST_H

#include "Orders.h"
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for seed

using namespace std;

const int MAX_LEVEL = 5;

class SkipOrderList {
private:
    struct Node {
        Order data;             // order object will be data
        vector<Node*> next;     //Pointers to the next nodes at various levels

        Node(const Order&  order, int level)
            : data(order), next(level, nullptr) {}
    };

    Node* head;                 // head node
    int maxLevel;               // max level of the skip list
    int currentLevel;           // current max level in use

    int randomLevel();          // generate a random level for a node

public:
    SkipOrderList(int MAX_LEVEL);       // constructor with a default max level
    ~SkipOrderList();                   // destructor

    void insert(const Order& order);    // insert an order into the list
    void display() const;               // display the skip list
};

#endif