#ifndef BSTORDERLIST_H
#define BSTORDERLIST_H
#include "Orders.h"
#include "ArrayOrderList.h"
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
    Node* searchNode(Node* node, const string& orderId) const;  // used to find a node
    Node* findMin(Node* node) const;                            // used to find min value in right tree
    void traverseInOrder(Node* node) const;                     // traverse
    void destroyTree(Node* node);                               // goodbye tree
    int calculateHeight(Node* node) const;

public:
    // constructor
    BstOrderList();
    // destructor
    ~BstOrderList();
    // required functions
    void addOrder(Order& order);                            // adds order object to the tree
    void removeOrder(string& orderId);                      // removes order object from the tree
    Order* searchByOrderId(const string& orderId) const;    // searches for an order by orderId
    void traverseInOrder() const;                           // traverses and prints list of orders

    // helpers
    Order* findMin() const;                                 // used to find min value of tree
    void fillBstFromFile(const string& filename);           // fills from file
    void loadFromArrayOrderList(ArrayOrderList& list);      // fills from array
    void exportTree(const std::string& filename) const;     // exports tree for graphics
    void exportNode(std::ofstream& file, Node* node) const;
    int getHeight() const;


};

#endif