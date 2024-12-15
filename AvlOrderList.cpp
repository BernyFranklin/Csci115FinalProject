#include "AvlOrderList.h"
#include "BstOrderList.h"
#include <fstream>

AvlOrderList::AvlOrderList() : root(nullptr) {}

AvlOrderList::~AvlOrderList() {
    // Use a post-order traversal to delete all nodes
    std::function<void(Node*)> deleteNodes = [&](Node* node) {
        if (node) {
            deleteNodes(node->left);
            deleteNodes(node->right);
            delete node;
        }
    };
    deleteNodes(root);
}

int AvlOrderList::getHeight(Node* node) const {
    return node ? node->height : -1;
}

int AvlOrderList::getHeight() const {return getHeight(root);}

int AvlOrderList::getBalanceFactor(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

//rotations
AvlOrderList::Node* AvlOrderList::rotateLeft(Node* node) {
    // rotate the nodes
    // step 1: set the new root to the right child of the current node
    Node* newRoot = node->right;
    // step 2: move the left subtree of newRoot to the right of the current node
    node->right = newRoot->left;
    // step 3: set the current node as the left child of the new root
    newRoot->left = node;

    // Update heights
    // step 4: update height of the current node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    // step 5: update the height of the new root
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));
    // step 6: return the new root of the rotated subtree
    return newRoot;
}

AvlOrderList::Node* AvlOrderList::rotateRight(Node* node) {
    // step 1: set the new root  to the left child of the current node
    Node* newRoot = node->left;
    // step 2: move the right subtree of the new root to the left of the current node
    node->left = newRoot->right;
    // step 3: set the current node as the right child of the new root
    newRoot->right = node;

    // Update heights
    // step 4: update the height of the current node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    // step 5: update the height of the new root
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));
    // step 6: return the new root of the rotated subtree
    return newRoot;
}

AvlOrderList::Node* AvlOrderList::rotateLeftRight(Node* node) {
    // rotate left
    node->left = rotateLeft(node->left);
    // rotate right and return
    return rotateRight(node);
}

AvlOrderList::Node* AvlOrderList::rotateRightLeft(Node* node) {
    // rotate right
    node->right = rotateRight(node->right);
    // rotate left and return
    return rotateLeft(node);
}

AvlOrderList::Node* AvlOrderList::insert(Node* node, const Order& order) {
    if (!node) {
        return new Node(order);
    }

    if (order.getId() < node->data.getId()) {
        node->left = insert(node->left, order);
    } else if (order.getId() > node->data.getId()) {
        node->right = insert(node->right, order);
    } else {
        return node; // Duplicate keys not allowed
    }

    // Update height
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Balance the tree
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (order.getId() < node->left->data.getId()) {
            return rotateRight(node); // Left-Left case
        } else {
            return rotateLeftRight(node); // Left-Right case
        }
    }

    if (balanceFactor < -1) {
        if (order.getId() > node->right->data.getId()) {
            return rotateLeft(node); // Right-Right case
        } else {
            return rotateRightLeft(node); // Right-Left case
        }
    }

    return node;
}

// required functions
void AvlOrderList::addOrder(const Order& order) {
    root = insert(root, order);
}

Order *AvlOrderList::searchByOrderId(const string &orderId) const {
    return searchNode(root, orderId);
}

Order* AvlOrderList::searchNode(Node* node, const std::string& orderId) const {
    if (node == nullptr) {
        return nullptr; // Base case: not found
    }

    if (orderId == node->data.getId()) {
        return &(node->data); // Match found
    }

    if (orderId < node->data.getId()) {
        return searchNode(node->left, orderId); // Search left subtree
    } else {
        return searchNode(node->right, orderId); // Search right subtree
    }
}

void AvlOrderList::traverseInOrder(Node* node) const {
    if (!node) return;

    traverseInOrder(node->left);
    node->data.displayOrder(); // Assuming displayOrder() is implemented in Order
    traverseInOrder(node->right);
}

void AvlOrderList::traverseInOrder() const {
    traverseInOrder(root);
}

// helper to perform in order traversal and collect orders
void collectInOrder(const BstOrderList::Node* node, vector<Order>& orders) {
    if (node == nullptr) return;

    // recursively collect left subtree
    collectInOrder(node->left, orders);

    // add current node's data
    orders.push_back(node->data);

    // recursively collect right subtree
    collectInOrder(node->right, orders);
}

void AvlOrderList::convertFromBst(const BstOrderList& bst) {
    // Step 1: Collect all orders from the BST in sorted order
    std::vector<Order> orders;
    collectInOrder(bst.root, orders); // Traverse the BST and collect its elements

    // Step 2: Clear the current AVL tree
    if (root != nullptr) {
        this->~AvlOrderList(); // Call destructor to free memory
        root = nullptr;
    }

    // Step 3: Insert all orders into the AVL tree
    for (const auto& order : orders) {
        addOrder(order); // Insert into the AVL tree
    }
}

AvlOrderList::Node* AvlOrderList::removeNode(Node* node, const std::string& orderId) {
    if (node == nullptr) {
        return nullptr; // Base case: node not found
    }

    if (orderId < node->data.getId()) {
        node->left = removeNode(node->left, orderId); // Traverse left
    } else if (orderId > node->data.getId()) {
        node->right = removeNode(node->right, orderId); // Traverse right
    } else {
        // Node to be deleted found

        // Case 1: Node has no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // Case 2: Node has one child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: Node has two children
        Node* temp = findMin(node->right); // Find the smallest node in the right subtree
        node->data = temp->data;           // Replace current node with the smallest node
        node->right = removeNode(node->right, temp->data.getId()); // Remove the smallest node
    }

    // Update height of the current node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // Rebalance the tree
    return balance(node);
}
void AvlOrderList::removeOrder(const std::string& orderId) {
    root = removeNode(root, orderId);
}

AvlOrderList::Node* AvlOrderList::findMin(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

AvlOrderList::Node* AvlOrderList::balance(Node* node) {
    int balanceFactor = getBalanceFactor(node);

    // Left-heavy
    if (balanceFactor > 1) {
        if (getBalanceFactor(node->left) >= 0) {
            return rotateRight(node); // Single right rotation
        } else {
            return rotateLeftRight(node); // Double left-right rotation
        }
    }

    // Right-heavy
    if (balanceFactor < -1) {
        if (getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node); // Single left rotation
        } else {
            return rotateRightLeft(node); // Double right-left rotation
        }
    }

    return node; // Already balanced
}

void AvlOrderList::exportTree(const std::string& filename) const {
    ofstream out(filename);

    if (!out.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    out << "digraph AVLTree {" << std::endl;

    if (root != nullptr) {
        exportNode(out, root);
    }

    out << "}" << std::endl;

    out.close();
    std::cout << "Tree exported to " << filename << std::endl;
}

void AvlOrderList::exportNode(std::ofstream& out, Node* node) const {
    if (node == nullptr) {
        return;
    }

    // Write the current node
    out << "  \"" << node->data.getId() << "\" [label=\""
        << node->data.getId() << "\\nPriority: " << node->data.getPriority()
        << "\\nDestination: " << node->data.getDestination()
        << "\"];" << std::endl;

    // Write edges to children
    if (node->left != nullptr) {
        out << "  \"" << node->data.getId() << "\" -> \"" << node->left->data.getId() << "\";" << std::endl;
        exportNode(out, node->left);
    }

    if (node->right != nullptr) {
        out << "  \"" << node->data.getId() << "\" -> \"" << node->right->data.getId() << "\";" << std::endl;
        exportNode(out, node->right);
    }
}





