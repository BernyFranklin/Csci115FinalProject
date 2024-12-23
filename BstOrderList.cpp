#include "BstOrderList.h"
#include "ArrayOrderList.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>

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
    Order* foundOrder = searchByOrderId(orderId);
    // if not found
    if (!foundOrder) {
        cerr << "\n\nOrder with ID " << orderId << " not found." << endl;
        return;
    }

    root = deleteNode(root, orderId);
}

// searches for an order by ordrId
Order* BstOrderList::searchByOrderId(const std::string &orderId) const {
    Node* result = searchNode(root, orderId);
    // return pointer to order or null
    return result ? &(result->data) : nullptr;
}

// traversal and print function
void BstOrderList::traverseInOrder() const {
    traverseInOrder(root);              // call the helper
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

    // traverse the tree to find the node to delete
    if (orderId < node->data.getId()) {
        node->left = deleteNode(node->left, orderId);       // go left
    }
    else if (orderId > node->data.getId()) {
        node->right = deleteNode(node->right, orderId);     // go right
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {    // found, delete
            // case 1: leaf node
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr){
            // case 2: one child (right)
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            // case 3: one child (left)
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else {
            // case 4: TWO children
            Node* temp = findMin(node->right);                                  // find the smallest node in the right subtree
            node->data = temp->data;                                                  // replace current data with successor's data
            node->right = deleteNode(node->right, temp->data.getId());  // remove the successor
        }
    }
    return node;
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
BstOrderList::Node* BstOrderList::findMin(BstOrderList::Node *node) const{
    if (node == nullptr) return nullptr;

    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}
Order* BstOrderList::findMin() const {
    Node* minNode = findMin(root);
    return minNode ? &(minNode->data) : nullptr;
}
// traversal helper
void BstOrderList::traverseInOrder(BstOrderList::Node *node) const {
    if (node == nullptr) return;            // empty subtree
    traverseInOrder(node->left);      // go left
    node->data.displayOrder();              // print to console
    traverseInOrder(node->right);     // go right
}
// fill the BST from our txt file
void BstOrderList::fillBstFromFile(const std::string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "\n\nError: could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string id, destination;
        int priority;

        if (getline(ss, id, ',') && ss >> priority && ss.ignore() && getline(ss, destination)) {
            Order order(id, priority, destination);
            addOrder(order);
        }
    }
    file.close();
}
// fill from a randomized array
void BstOrderList::loadFromArrayOrderList(ArrayOrderList& list) {
    // create a vector of Order objects from the ArrayOrderList
    vector<Order> orders;
    for (int i = 0; i < list.getSize(); i++) {
        orders.push_back(list.getOrder(i));
    }

    // shuffle the orders
    random_device rd;
    mt19937 g(rd());
    shuffle(orders.begin(), orders.end(), g);

    // insert the shuffled orders into the BST
    for (auto& order : orders) {
        addOrder(order);
    }
}
// for visualization
void BstOrderList::exportTree(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file << "digraph BST {" << std::endl;
    exportNode(file, root);
    file << "}" << std::endl;

    file.close();
}
void BstOrderList::exportNode(std::ofstream& file, Node* node) const {
    if (node == nullptr) return;

    if (node->left != nullptr) {
        file << "\"" << node->data.getId() << "\" -> \"" << node->left->data.getId() << "\";" << std::endl;
    }
    if (node->right != nullptr) {
        file << "\"" << node->data.getId() << "\" -> \"" << node->right->data.getId() << "\";" << std::endl;
    }

    exportNode(file, node->left);
    exportNode(file, node->right);
}
// for comparing heights
int BstOrderList::getHeight() const {
    return calculateHeight(root);
}
int BstOrderList::calculateHeight(BstOrderList::Node *node) const {
    if (node == nullptr) {
        return -1;          // empty subtree
    }

    // recursively calculate the height of the left and right sub trees
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    // height of the current node is 1 + max of left and right heights
    return 1 + max(leftHeight, rightHeight);
}