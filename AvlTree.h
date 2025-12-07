#pragma once

template <typename KeyType, typename ValueType>

class AvlTree {
private:
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


public:
    Node* find(const KeyType& key) const // doesnt change tree, might change node
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
            root = new Node{key, value}; // need to define c'tor to Node to allow this?
        } // left,right,parent all set by default to null?

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
            if (key > current->key) {
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
        return true;
    }


    bool erase(const KeyType& key) // false if doesnt exist
    {
        // later need to divide to functions

        Node* toDelete = find(key);
        if (toDelete == nullptr) {
            // key not in tree
            return false;
        }
        // node in tree
        if (root == toDelete) {
            root = nullptr;
        }
        else if (toDelete->left == nullptr && toDelete->right == nullptr) {
            // the node is a leaf
            if (toDelete->parent->left == toDelete) {
                //  node is a left son
                toDelete->parent->left = nullptr;
            }
            if (toDelete->parent->right == toDelete) {
                //  node is a right son
                toDelete->parent->right = nullptr;
            }
        }
        // node is not a leaf
        else if (toDelete->right == nullptr) {
            // node only had left son
            if (toDelete->parent->right == toDelete) {
                toDelete->parent->right = toDelete->left;
            }
            if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = toDelete->left;
            }
            // add is left is right boolean function
        }
        if (toDelete->left == nullptr) {
            // has only right son
            if (toDelete->parent->right == toDelete) {
                toDelete->parent->right = toDelete->right;
            }
            if (toDelete->parent->left == toDelete) {
                toDelete->parent->left = toDelete->right;
            }
        }
        else {
            // toDelete has 2 sons:
        }
        delete toDelete;
        return true;
    }
};
