#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>
#include "nodedata.h"

/*
-------------------------------------------------------------------------------
File: bintree.h

Authors: Destiny Rebman and Parisa Soltanian

Description:
    This file defines the BinTree class, which implements a Binary Search Tree
    (BST) storing NodeData* objects. The tree owns all NodeData pointers that
    are successfully inserted and is responsible for deleting them.

Assumptions:
    - No duplicate values are stored in the tree.
    - Smaller values go to the left subtree.
    - Larger values go to the right subtree.
    - getHeight() must work for a general binary tree (not assuming BST order).
    - bstreeToArray() empties the tree and transfers NodeData* into the array.
    - arrayToBSTree() builds a balanced BST and sets array elements to NULL.
-------------------------------------------------------------------------------
*/

class BinTree {

    friend std::ostream& operator<<(std::ostream&, const BinTree&);

public:
    // ---------------- Constructors / Destructor ----------------

    // Default constructor
    // Preconditions: None
    // Postconditions: Creates an empty tree.
    BinTree();

    // Copy constructor (deep copy)
    // Preconditions: None
    // Postconditions: Creates a new tree that is a deep copy of other.
    BinTree(const BinTree&);

    // Destructor
    // Preconditions: None
    // Postconditions: All dynamically allocated memory is freed.
    ~BinTree();

    // ---------------- Assignment / Comparison ----------------

    // Assignment operator (deep copy)
    BinTree& operator=(const BinTree&);

    // Returns true if both trees have identical structure and data.
    bool operator==(const BinTree&) const;

    // Returns true if trees differ in structure or data.
    bool operator!=(const BinTree&) const;

    // ---------------- Accessors ----------------

    // Returns true if tree is empty.
    bool isEmpty() const;

    // Makes tree empty.
    void makeEmpty();

    // Inserts NodeData* into proper BST location.
    // Returns false if duplicate.
    bool insert(NodeData*);

    // Retrieves pointer to matching NodeData.
    bool retrieve(const NodeData&, NodeData*&) const;

    // Returns height of node containing value.
    int getHeight(const NodeData&) const;

    // Converts BST to sorted array (inorder).
    void bstreeToArray(NodeData* []);

    // Builds balanced BST from sorted array.
    void arrayToBSTree(NodeData* []);

    // Displays tree sideways.
    void displaySideways() const;

private:

    struct Node {
        NodeData* data;
        Node* left;
        Node* right;
    };

    Node* root;

    // ----------- Private Utility Functions -----------

    void makeEmptyHelper(Node*&);
    Node* copyHelper(const Node*);
    bool equalsHelper(Node*, Node*) const;

    bool insertHelper(Node*&, NodeData*);
    bool retrieveHelper(Node*, const NodeData&, NodeData*&) const;

    Node* findNode(Node*, const NodeData&) const;
    int heightHelper(Node*) const;

    void inorderHelper(Node*, std::ostream&) const;

    void inorderToArray(Node*, NodeData*[], int&);
    Node* arrayToBSTreeHelper(NodeData*[], int, int);

    void sideways(Node*, int) const;
};

#endif