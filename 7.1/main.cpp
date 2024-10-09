#include <iostream>
#include <queue>
using namespace std;


struct Node {
    double value;
    Node* left;
    Node* right;
};

class BinarySearchTree {
private:
    Node* root;
    int nodeCount;

    // Private helper functions
    Node* insertNode(Node* node, double value);
    void symmetricTraversal(Node* node);
    double calculateAverage(Node* node);
    int findPathLength(Node* node, double value, int currentLength);
    double calculateSum(Node* node);

public:
    BinarySearchTree() : root(nullptr), nodeCount(0) {}

    // Public functions
    void insertElement(double value);
    void symmetricTraversal();
    double calculateAverage();
    int findPathLength(double value);
};

Node* BinarySearchTree::insertNode(Node* node, double value) {
    if (node == nullptr) {
        nodeCount++;
        node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
    } else if (value < node->value) {
        node->left = insertNode(node->left, value);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value);
    }
    return node;
}

void BinarySearchTree::insertElement(double value) {
    root = insertNode(root, value);
}

void BinarySearchTree::symmetricTraversal(Node* node) {
    if (node != nullptr) {
        symmetricTraversal(node->left);
        std::cout << node->value << " ";
        symmetricTraversal(node->right);
    }
}

void BinarySearchTree::symmetricTraversal() {
    symmetricTraversal(root);
    std::cout << std::endl;
}

double BinarySearchTree::calculateSum(Node* node){
    if (node == nullptr){
        return 0.0;
    }else{
        return node->value + calculateSum(node->left)+calculateSum(node->right);
    }
}

double BinarySearchTree::calculateAverage(Node* node) {
    if (node == nullptr){
        return 0.0;
    }else{
        double sum = calculateSum(root);
        return sum/nodeCount;
    }
}

double BinarySearchTree::calculateAverage() {
    return calculateAverage(root);
}

int BinarySearchTree::findPathLength(Node* node, double value, int currentLength) {
    if (node == nullptr) {
        return -1;
    } else if (node->value == value) {
        return currentLength;
    } else if (value < node->value) {
        return findPathLength(node->left, value, currentLength + 1);
    } else {
        return findPathLength(node->right, value, currentLength + 1);
    }
}

int BinarySearchTree::findPathLength(double value) {
    return findPathLength(root, value, 0);
}

int main() {
    BinarySearchTree bst;
    int choice;
    double value;

    while (true) {
        std::cout << "Binary Search Tree Menu:" << std::endl;
        std::cout << "1. Insert Element" << std::endl;
        std::cout << "2. Symmetric Traversal" << std::endl;
        std::cout << "3. Calculate Average" << std::endl;
        std::cout << "4. Find Path Length" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter value to insert: ";
                std::cin >> value;
                bst.insertElement(value);
                break;
            case 2:
                bst.symmetricTraversal();
                break;
            case 3:
                std::cout << "Average value: " << bst.calculateAverage() << std::endl;
                break;
            case 4:
                std::cout << "Enter value to find path length: ";
                std::cin >> value;
                std::cout << "Path length: " << bst.findPathLength(value) << std::endl;
                break;
            case 5:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}