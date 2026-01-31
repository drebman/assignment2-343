# _Assignment 2: 343_

## <ins>**This is the Assignment 2 for CSS 343, which allows pairs**</ins>

### Requirements:

🌳 Binary Search Tree – BinTree
📌 Overview

This project implements a Binary Search Tree (BST) class named BinTree.
The tree stores NodeData* objects and supports building trees from an input file.

⚠ The remove function is not required for this project.

The project may be completed individually or in pairs.

📂 Input File Format

The program reads a data file (e.g., data2.txt) containing multiple lines of string data.

Example (data2.txt)
iii not tttt eee r not and jj r eee pp r sssss eee not tttt ooo ff m m y z $$
b a c b a c $$
c b a $$

Rules

Each line builds one tree

Each line ends with "$$"

Duplicate strings are discarded

Smaller strings go to the left

Larger strings go to the right

🌲 Example Tree

The first line of data2.txt produces:

                iii
              /     \
           eee        not
          /   \      /   \
        and    ff   jj   tttt
                 \      /    \
                  m     r      y
                       / \       \
                      pp sssss      z
                         /
                       ooo

🛠 Implementation Requirements

You must use the provided:

nodedata.h

nodedata.cpp

Each tree node must contain:

NodeData* data;
Node* left;
Node* right;

✅ Required Components
🔹 Constructors & Destructor

Default constructor (creates empty tree)

Copy constructor (deep copy)

Destructor (properly frees all memory)

Valgrind is required.
Points will be deducted for “definitely lost” memory leaks.

🔹 Operator Overloads
Assignment
operator=


Must perform a deep copy.

Equality
operator==
operator!=


Two trees are equal if:

They contain the same data

They have the same structure

🔹 Accessor Functions
1️⃣ Inorder Output
operator<<


Displays tree using inorder traversal

NodeData handles its own formatting

2️⃣ Retrieve
bool retrieve(const NodeData&, NodeData*&);


Returns true if found

Second parameter points to actual object in tree

Returns false if not found

3️⃣ getHeight
int getHeight(const NodeData&) const;


⚠ Special Rule:
For this function only, treat the tree as a general binary tree.

You may NOT assume BST ordering.

Height definition:

Leaf node = 1

Parent of leaf = 2

Value not found = 0

🔹 Other Required Functions
Insert
bool insert(NodeData*);


Inserts at correct BST location

No duplicates allowed

Returns true if inserted

Returns false if duplicate

bstreeToArray
void bstreeToArray(NodeData* []);


Uses inorder traversal

Fills a statically allocated array of 100 elements

Leaves tree empty

No bounds checking required

Example result:

and, eee, ff, iii, jj, m, not, ooo, pp, r, sssss, tttt, y, z

arrayToBSTree
void arrayToBSTree(NodeData* []);


Builds a balanced BST

Root index = (low + high) / 2

Leaves array filled with NULL

Example balanced structure:

                not
              /     \
            ff       sssss
           /  \      /    \
        and   jj   pp     y
          \   / \     \   / \
          eee iii m   ooo r tttt z

📎 Supporting Files

data2.txt – Input file

nodedata.h

nodedata.cpp

lab2.cpp – Provided main()

lab2output – Expected output

classAndSideway.txt – Sideways display helper functions

📦 Submission Requirements

Follow Assignment 1 rules and formatting guidelines

Must compile and run with lab2.cpp

Must pass Valgrind

No “definitely lost” memory leaks
