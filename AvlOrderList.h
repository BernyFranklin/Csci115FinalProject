#ifndef AVLORDERLIST_H
#define AVLORDERLIST_H

#include "Orders.h"
#include "BstOrderList.h"
#include <iostream>
#include <algorithm>

class AvlOrderList {
private:
    // Node structure for the AVL tree
    struct Node {
        Order data;
        Node* left;
        Node* right;
        int height;

        Node(const Order& order)
                : data(order), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root; // Root of the AVL tree

    // Helper functions
    int getHeight(Node* node) const;
    int getBalanceFactor(Node* node) const;
    Node* balance(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);

    Node* insert(Node* node, const Order& order);
    Node* removeNode(Node* node, const string& orderId);
    Order* searchNode(Node* node, const string& orderId) const;
    Node* findMin(Node* node) const;

    void traverseInOrder(Node* node) const;

public:
    AvlOrderList();
    ~AvlOrderList();

    void addOrder(const Order& order);
    void removeOrder(const string& orderId);
    Order* searchByOrderId(const string& orderId) const;
    void convertFromBst(const BstOrderList& bst);
    void traverseInOrder() const;
    int getHeight() const;
};

#endif
