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
    Node* insertNode(Node* node, Order& order);                 // inserts node...
    Node* deleteNode(Node* node, const string& orderId);        // deletes node, pretty self-explanatory
    Node* findMin(Node* node);                                  // used to find min value in right tree
    Node* searchNode(Node* node, const string& orderId) const;  // used to find a node
    void destroyTree(Node* node);                               // goodbye tree

public:
    // constructor
    BstOrderList();
    // destructor
    ~BstOrderList();
    // required functions
    void addOrder(Order& order);                            // adds order object to the tree
    void removeOrder(string& orderId);                      // removes order object from the tree
    Order* searchByOrderId(const string& orderId) const;    // searches for an order by orderId
};

#endif