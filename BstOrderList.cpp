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

// removes order object from the tree
void BstOrderList::removeOrder(std::string &orderId) {
    root = deleteNode(root, orderId);
}

// searches for an order by ordrId
Order* BstOrderList::searchByOrderId(const std::string &orderId) const {
    Node* result = searchNode(root, orderId);
    // return pointer to order or null
    return result ? &(result->data) : nullptr;
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
// deletes node from tree
BstOrderList::Node* BstOrderList::deleteNode(BstOrderList::Node *node, const std::string &orderId) {
    if (node == nullptr) {
        cerr << "\n\nOrder with ID " << orderId << " not found." << endl;
        return nullptr;
    }

    // traverse the tree to find
}
// searches the nodes recursively
BstOrderList::Node* BstOrderList::searchNode(BstOrderList::Node *node, const std::string &orderId) const {
    if (node == nullptr || node->data.getId() == orderId) {
        return node;                                        // found
    }

    if (orderId < node->data.getId()) {
        return searchNode(node->left, orderId);       // search left
    }
    else {
        return searchNode(node->right, orderId);      // search right
    }
}
// finds the minimum
