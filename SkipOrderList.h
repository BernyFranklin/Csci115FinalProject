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

    // getter
    Order getOrder(const string& orderId) const;                    // gets order object
    // functions being tested
    void addOrder(const Order& order);                              // addOrder an order into the list
    void removeOrder(const string &orderId);                        // delete an order by orderId
    Node *searchByOrderId(const string& orderId) const;             // searchByOrderId by orderId
    void updatePriority(const string& orderId, int newPriority);    // update priority by orderId

    // other functions
    void display() const;                                           // display the skip list
    void loadFromArray(const ArrayOrderList& arrayList);            // load skip list from array
};

#endif