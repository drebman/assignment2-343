/*
-------------------------------------------------------------------------------
File: bintree.cpp

Authors: Destiny Rebman and Parisa Soltanian

Description:
    Implementation file for the BinTree class. This class implements a
    Binary Search Tree (BST) storing NodeData* objects.

Memory Management:
    - The tree owns all NodeData pointers successfully inserted.
    - Destructor and makeEmpty() delete all Nodes and NodeData objects.
    - bstreeToArray() transfers NodeData pointers to the array and deletes only the Node structures.
    - arrayToBSTree() rebuilds a balanced BST and nulls array elements.

Assumptions:
    - No duplicate NodeData values are stored.
    - BST ordering property is maintained for insert and retrieve.
    - getHeight() works on a general binary tree (not assuming BST order).
-------------------------------------------------------------------------------
*/

#include "bintree.h"
#include <iostream>

using namespace std;


// ----------------------------- Constructor ----------------------------------
// Preconditions: None
// Postconditions: Creates an empty tree.
BinTree::BinTree() {
    root = NULL;
}


// -------------------------- Copy Constructor --------------------------------
// Preconditions: None
// Postconditions: Creates a deep copy of the given tree.
BinTree::BinTree(const BinTree& other) {
    root = copyHelper(other.root);
}


// ------------------------------ Destructor ----------------------------------
// Preconditions: None
// Postconditions: All dynamically allocated memory is freed.
BinTree::~BinTree() {
    makeEmpty();
}


// ------------------------------- isEmpty ------------------------------------
// Preconditions: None
// Postconditions: Returns true if tree is empty.
bool BinTree::isEmpty() const {
    return root == NULL;
}


// ------------------------------- makeEmpty ----------------------------------
// Preconditions: None
// Postconditions: Deletes all nodes and NodeData objects in tree.
void BinTree::makeEmpty() {
    makeEmptyHelper(root);
}

void BinTree::makeEmptyHelper(Node*& current) {
    if (current != NULL) {
        makeEmptyHelper(current->left);
        makeEmptyHelper(current->right);

        delete current->data;
        delete current;
        current = NULL;
    }
}


// -------------------------- Assignment Operator ------------------------------
// Preconditions: None
// Postconditions: Replaces current tree with deep copy of other.
BinTree& BinTree::operator=(const BinTree& other) {
    if (this != &other) {
        makeEmpty();
        root = copyHelper(other.root);
    }
    return *this;
}


// ------------------------------ Equality ------------------------------------
// Preconditions: None
// Postconditions: Returns true if trees have identical structure and data.
bool BinTree::operator==(const BinTree& other) const {
    return equalsHelper(root, other.root);
}

bool BinTree::operator!=(const BinTree& other) const {
    return !(*this == other);
}

bool BinTree::equalsHelper(Node* a, Node* b) const {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;

    return (*a->data == *b->data)
        && equalsHelper(a->left, b->left)
        && equalsHelper(a->right, b->right);
}


// -------------------------------- Insert ------------------------------------
// Preconditions: data is a valid NodeData pointer.
// Postconditions: Inserts into BST if no duplicate; returns true if inserted.
bool BinTree::insert(NodeData* data) {
    return insertHelper(root, data);
}

bool BinTree::insertHelper(Node*& current, NodeData* data) {
    if (current == NULL) {
        current = new Node;
        current->data = data;
        current->left = NULL;
        current->right = NULL;
        return true;
    }

    if (*data == *current->data)
        return false;

    if (*data < *current->data)
        return insertHelper(current->left, data);

    return insertHelper(current->right, data);
}


// -------------------------------- Retrieve ----------------------------------
// Preconditions: None
// Postconditions: If target exists, result points to stored NodeData.
bool BinTree::retrieve(const NodeData& target, NodeData*& result) const {
    return retrieveHelper(root, target, result);
}

bool BinTree::retrieveHelper(Node* current,
                            const NodeData& target,
                            NodeData*& result) const {
    if (current == NULL) return false;

    if (*current->data == target) {
        result = current->data;
        return true;
    }

    if (target < *current->data)
        return retrieveHelper(current->left, target, result);

    return retrieveHelper(current->right, target, result);
}


// -------------------------------- getHeight ---------------------------------
// Preconditions: None
// Postconditions: Returns height of node containing target.
//                 Returns 0 if target not found.
int BinTree::getHeight(const NodeData& target) const {
    Node* found = findNode(root, target);
    if (found == NULL) return 0;
    return heightHelper(found);
}

BinTree::Node* BinTree::findNode(Node* current,
                                const NodeData& target) const {
    if (current == NULL) return NULL;

    if (*current->data == target)
        return current;

    Node* leftResult = findNode(current->left, target);
    if (leftResult != NULL)
        return leftResult;

    return findNode(current->right, target);
}

int BinTree::heightHelper(Node* current) const {
    if (current == NULL) return 0;

    int leftHeight = heightHelper(current->left);
    int rightHeight = heightHelper(current->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}


// ------------------------------ operator<< ----------------------------------
// Preconditions: None
// Postconditions: Outputs tree contents in inorder traversal.
ostream& operator<<(ostream& out, const BinTree& tree) {
    tree.inorderHelper(tree.root, out);
    out << endl;
    return out;
}

void BinTree::inorderHelper(Node* current, ostream& out) const {
    if (current != NULL) {
        inorderHelper(current->left, out);
        out << *current->data << " ";
        inorderHelper(current->right, out);
    }
}


// ---------------------------- bstreeToArray ---------------------------------
// Preconditions: arr is a 100-element array initialized to NULL.
// Postconditions: Tree becomes empty; arr filled in sorted order.
void BinTree::bstreeToArray(NodeData* arr[]) {
    int index = 0;
    inorderToArray(root, arr, index);
    root = NULL;
}

void BinTree::inorderToArray(Node* current,
                            NodeData* arr[],
                            int& index) {
    if (current != NULL) {
        inorderToArray(current->left, arr, index);

        arr[index++] = current->data;

        inorderToArray(current->right, arr, index);

        delete current;   // delete node only (not data)
    }
}


// --------------------------- arrayToBSTree ----------------------------------
// Preconditions: arr contains sorted NodeData* values.
// Postconditions: Balanced BST is built; arr elements set to NULL.
void BinTree::arrayToBSTree(NodeData* arr[]) {
    int size = 0;
    while (size < 100 && arr[size] != NULL)
        size++;

    root = arrayToBSTreeHelper(arr, 0, size - 1);
}

BinTree::Node* BinTree::arrayToBSTreeHelper(NodeData* arr[],
                                            int low, int high) {
    if (low > high) return NULL;

    int mid = (low + high) / 2;

    Node* newNode = new Node;
    newNode->data = arr[mid];
    arr[mid] = NULL;

    newNode->left = arrayToBSTreeHelper(arr, low, mid - 1);
    newNode->right = arrayToBSTreeHelper(arr, mid + 1, high);

    return newNode;
}
