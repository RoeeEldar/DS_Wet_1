#pragma once

template <typename KeyType, typename ValueType>

class AvlTree {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* parent;
        Node* left;
        Node* right;
        int height; // to calc balance factor, correct to hold here?
    };

    Node* root; // maybe need to  set to null?

    // rolls...
    // blance factor calc
    // helper function to destroy tree starting from root - if using normal pointers


public:
    Node* find(const KeyType& key) const // doesnt change tree, might change node
    // if return as not smart pointer, others might access it after earased..
    {
        Node* current = this -> root;

        while (current != nullptr) { // search until end of tree

            if (key == current -> key) { // key found, return pointer to node
                return current;
            }
            if (key < current -> key) { // searching for smaller key, search left subtree
                current = current.left;
            }
            if (key > current -> key) {// searching for bigger key, search right subtree
                current -> current.right;
            }
        }
        // reached end of tree, key not found
        return nullptr;


    } // done;

    bool insert(const KeyType& key, const ValueType& value) // false if exists
    {
    }

    bool erase(const KeyType& key) // false if doesnt exist
    {
    }
};
