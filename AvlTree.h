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
        int height; // to calc balance factor
    };
    Node* root = nullptr;

    // rolls...
    // blance factor calc
    // helper function to destroy tree starting from root - if using normal pointers


public:
    Node* find (const KeyType& key) const; // doesnt change tree, might change node
    // if return as not smart pointer, others might access it after earased..
    bool insert (const KeyType& key, const ValueType& value); // false if exists
    bool erase (const KeyType& key); // false if doesnt exist

};
