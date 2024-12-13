#include "BstOrderList.h"

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