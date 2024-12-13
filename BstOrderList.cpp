#include "BstOrderList.h"
#include <iostream>
using namespace std;
// constructor
BstOrderList::BstOrderList() : root(nullptr){}

// destructor
BstOrderList::~BstOrderList() {
    destroyTree(root);
}

// used for our destructor
void BstOrderList::destroyTree(BstOrderList::Node *node) {
    if (node != nullptr) {
        // recursively delete left and right subtress
        destroyTree(node->left);
        destroyTree(node->right);

        // delete current node
        delete node;
    }
}

// required functions
// adds order object to tree
void BstOrderList::addOrder(Order &order) {
    root = insertNode(root, order);
}

// helper functions
// inserts a node into the tree
BstOrderList::Node* BstOrderList::insertNode(BstOrderList::Node *node, Order &order) {
    if (node == nullptr) {
        // create a new node if we reach a null position
        return new Node(order);
    }

    // compare orderId to determine placement
    if (order.getId() < node->data.getId()) {
        node->left = insertNode(node->left, order);
    }
    else if (order.getId() > node->data.getId()) {
        node->right = insertNode(node->right, order);
    }
    else {
        // duplicate orderId, do nothing
        cerr << "\n\nDuplicate orderId: " << order.getId() << " not inserted." << endl;
    }
    return node;
}