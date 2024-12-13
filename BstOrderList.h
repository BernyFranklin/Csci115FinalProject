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

    void destroyTree(Node* node);

public:
    BstOrderList();
    ~BstOrderList();
};

#endif