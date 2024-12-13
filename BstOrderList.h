#ifndef BSTORDERLIST_H
#define BSTORDERLIST_H
#include "Orders.h"
#include <string>

class BstOrderList {
private:
    struct Node {
        Order data;
        Node* left;
        Node* right;

        Node(const Order& order) : data(order), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Node* insertNode(Node* node, Order& order);
    void destroyTree(Node* node);

public:
    // constructor
    BstOrderList();
    // destructor
    ~BstOrderList();
    // required functions
    void addOrder(Order& order);        // adds order object to the tree
};

#endif