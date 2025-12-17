#pragma once
#include <stdexcept>

template <typename KeyType, typename ValueType>

class AvlTree {
    struct Node {
        KeyType key;
        ValueType value;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
        int height = 0; // to calc balance factor, correct to hold here?
        // need to add height to all functions
    };

    Node* root = nullptr;

    // rolls...
    // blance factor calc
    // helper function to destroy tree starting from root - if using normal pointers
    // destructor for Node and or for AvlTree
    // need to  update height for nodes where its required

    bool nodeIsRightSon(Node* node) const {
        if (node->parent->right == node) {
            return true;
        }
        return false;
    }

    Node* findSuccessor(Node* node) const {
        // caller must ensure that node has right son before function call
        if (node->right == nullptr) {
            throw std::runtime_error("Error, next in order requires right son");
        }
        Node* temp = node;
        temp = temp->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }

    void swap(Node* current, Node* successor) {
        KeyType tempKey = current->key;
        ValueType tempValue = current->value;

        current->key = successor->key;
        current->value = successor->value;

        successor->key = tempKey;
        successor->value = tempValue;
    }

    void updateHeight(Node* node) {
        // height of node is the maximum of heights of both subtrees +1
        // null height is -1
        int leftHeight = (node->left) ? node->left->height : -1;
        int rightHeight = (node->right) ? node->right->height : -1;
        if (leftHeight >= rightHeight) {
            node->height = leftHeight + 1;
        }
        else {
            node->height = rightHeight + 1;
        }
    }

    void updateTreeHeights(Node* node) {
        // to be used in insert function
        while (node != nullptr) {
            int oldHeight = node->height;
            updateHeight(node);
            if (node->height == oldHeight) {
                // if the height stops changing at some point before the root,
                // the height of nodes above it also won't change
                break;
            }
            node = node->parent;
        }
    }

    bool erase(Node* toDelete) {
        if (toDelete == nullptr) {
            // key not in tree
            return false;
        }

        if (toDelete->left == nullptr && toDelete->right == nullptr) {
            // the node is a leaf
            if (toDelete->parent != nullptr) {
                // the node is not the root

                if (nodeIsRightSon(toDelete)) {
                    toDelete->parent->right = nullptr;
                }
                else {
                    toDelete->parent->left = nullptr;
                }
            }
            else { root = nullptr; } // toDelete is root and is leaf
        }
        // node is not a leaf
        else if (toDelete->right == nullptr || toDelete->left == nullptr) {
            // node has exactly one child

            Node* child = toDelete->right ? toDelete->right : toDelete->left;
            if (toDelete->parent != nullptr) {
                // node is not root
                if (nodeIsRightSon(toDelete)) {
                    toDelete->parent->right = child;
                }
                else {
                    toDelete->parent->left = child;
                }
            }
            else {
                //node is root
                root = child;
            }

            child->parent = toDelete->parent;
        }
        else {
            // toDelete has 2 sons:
            // find next Node by inorder:

            Node* successor = findSuccessor(toDelete);
            swap(toDelete, successor);
            erase(successor); // is always either leaf, or has only right son
            // if it had left son, it would have been the successor
            return true; // because we swapped by value
        }

        updateTreeHeights(toDelete -> parent);
        delete toDelete;
        return true;
    }

    void destruct(Node* root) {
        if (root == nullptr) {
            return;
        }
        destruct(root->left); // destruct left sub-tree
        destruct(root->right); // destruct right sub-tree
        delete root;
    }

public
:
    ~AvlTree() {
        // need to traverse in postorder and destroy each node
        destruct(root);
    }

    Node* find(const KeyType& key) const // doesnt change tree, might change node - (why?)
    // if return as not smart pointer, others might access it after earased..
    {
        Node* current = root;
        while (current != nullptr) {
            // search until end of tree

            if (key == current->key) {
                return current;
            }
            if (key < current->key) {
                //search left subtree
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        // key not found
        return nullptr;
    }

    bool insert(const KeyType& key, const ValueType& value) // false if key already in tree
    {
        // general implementation for binary tree, need to add rolls and such

        if (root == nullptr) {
            // tree is empty, create new node and set it as root
            root = new Node{key, value};
            return true;
        }

        // tree is not empty
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                return false;
            }
            if (key < current->key) {
                // search left subtree
                parent = current;
                current = current->left;
            }
            else if (key > current->key) {
                // search right subtree
                parent = current;
                current = current->right;
            }
        }
        if (key < parent->key) {
            parent->left = new Node{key, value, parent};
        }
        if (key > parent->key) {
            parent->right = new Node{key, value, parent};
        }

        updateTreeHeights(parent);
        return true;
    }

    bool erase(const KeyType& key) // false if doesnt exist
    {
        Node* toDelete = find(key);
        return erase(toDelete);
    }
};
