#ifndef SKIP_ORDER_LIST_H
#define SKIP_ORDER_LIST_H

#include "Orders.h"
#include "ArrayOrderList.h"
#include <utility>
#include <vector>
#include <cstdlib>  // for rand()
#include <ctime>    // for seed

using namespace std;

class SkipOrderList {
private:
    struct Node {
        Order data;             // order object will be data
        vector<Node*> next;     //Pointers to the next nodes at various levels

        Node(const Order& order, int level)
            : data(order), next(level, nullptr) {}
    };

    Node* head;                 // head node
    int maxLevel;               // max level of the skip list
    int currentLevel;           // current max level in use

    int randomLevel();          // generate a random level for a node

public:
    SkipOrderList(int maxLevel = 5);       // constructor with a default max level
    ~SkipOrderList();                   // destructor

    void loadFromArray(const ArrayOrderList& arrayList);        // load skip list from array
    void insert(const Order& order);                            // insert an order into the list
    void deleteOrder(const string& orderId);                    // delete an order by orderId
    void search(const string& orderId) const;                   // search by orderId
    void display() const;                                       // display the skip list
};

#endif