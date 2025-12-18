#pragma once
#include <cassert>

template <typename KeyType, typename ValueType>
class AvlTree;

template <typename KeyType, typename ValueType>
class Node {
    friend class AvlTree<KeyType, ValueType>;
    KeyType key;
    ValueType value;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0; // to calc balance factor, correct to hold here?
    // need to add height to all functions
    Node(KeyType k, ValueType v, Node* p = nullptr)
        : key(k), value(v), parent(p) {}

public:

    ValueType& getValue() {
        return value;
    }

};

template <typename KeyType, typename ValueType>
class AvlTree {
    using Node = Node<KeyType,ValueType>;

    Node* root = nullptr;

    static bool nodeIsRightSon(Node* node)
    {
        // must make sure it's not null before calling function
        if (node->parent->right == node) {
            return true;
        }
        return false;
    }

    Node* findSuccessor(Node* node) const {
        // caller must ensure that node has right son before function call
        assert(node && node->right != nullptr);
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

    static void updateNodeHeight(Node* node) {
        // height of node is the maximum of heights of both subtrees +1
        // null height is -1
        const int leftHeight = node->left ? node->left->height : -1;
        const int rightHeight = node->right ? node->right->height : -1;
        if (leftHeight >= rightHeight) {
            node->height = leftHeight + 1;
        }
        else {
            node->height = rightHeight + 1;
        }
    }

    void updateTreeHeights(Node* node) {
        while (node != nullptr) {
            int oldHeight = node->height;
            updateNodeHeight(node);
            if (node->height == oldHeight) {
                // if the height stops changing at some point before the root,
                // the height of nodes above it also won't change
                break;
            }
            node = node->parent;
        }
    }

    static int getHeight(Node* node) {
        return node == nullptr ? -1 : node->height;
    };

    int balanceFactor(Node* node) {
        assert(node != nullptr);
        //if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void destruct(Node* currentRoot) {
        if (currentRoot == nullptr) {
            return;
        }
        destruct(currentRoot->left); // destruct left subtree
        destruct(currentRoot->right); // destruct right subtree
        delete currentRoot;
    }

    bool rollHelper(Node* p) {
        // returns if a roll has been committed

        const int bf = balanceFactor(p);
        if (bf != -2 && bf != 2) {
            return false;
        }

        if (bf == 2) {
            // if bf is 2, we're promised that p has left son
            if (balanceFactor(p->left) == -1) {
                rollLR(p);
            }
            else { rollLL(p); }
        }
        else {
            // if bf is -2, we're promised that p has right son
            if (balanceFactor(p->right) == 1) {
                rollRL(p);
            }
            else { rollRR(p); }
        }
        return true;
    }

    void insertReBalance(Node* node) {
        // input node is newly inserted node - which is always a leaf
        while (node->parent) {
            Node* p = node->parent;
            if (p->height >= node->height + 1) {
                // adding node didn't change height of parent therefore didn't
                // change balance factor of any node above parent therefore tree
                // is still balanced
                return;
            }
            p->height = node->height + 1; // update height

            if (rollHelper(p)) {
                return;
            }
            node = p;
        }
    }

    void eraseReBalance(Node* node) {
        // input node is parent of newly removed node
        while (node) {

            updateNodeHeight(node); // update height

            rollHelper(node); // determines if roll is necessary and rolls

            node = node -> parent;
        }
    }

    void rollRR(Node* B) {
        // b is the node where the balance factor is disrupted
        assert(B != nullptr);
        Node* A = B->right;
        assert(A != nullptr);
        Node* AL = A->left;
        // make the right son of A the left son of B
        B->right = AL;
        if (AL != nullptr) {
            AL->parent = B;
        }
        A->parent = B->parent;
        if (B == root) {
            // it doesnt have a parent
            root = A;
        }
        else if (nodeIsRightSon(B)) {
            B->parent->right = A;
        }
        else {
            // B is left son
            B->parent->left = A;
        }
        // rotate A,B
        A->left = B;
        B->parent = A;

        // update heights of changed nodes:
        // update height of B before that of A, because B is now son of A
        updateNodeHeight(B);
        updateNodeHeight(A);
    }

    void rollRL(Node* C) {
        assert(C!= nullptr);
        Node* A = C->right;
        rollLL(A);
        rollRR(C);
    }

    void rollLL(Node* B) {
        // b is the node where the balance factor is disrupted
        assert(B != nullptr);
        Node* A = B->left;
        assert(A != nullptr);
        Node* AR = A->right;
        // make the right son of A the left son of B
        B->left = AR;
        if (AR != nullptr) {
            AR->parent = B;
        }
        A->parent = B->parent;
        if (B == root) {
            // it doesnt have a parent
            root = A;
        }
        else if (nodeIsRightSon(B)) {
            B->parent->right = A;
        }
        else {
            // B is left son
            B->parent->left = A;
        }
        // rotate A,B
        A->right = B;
        B->parent = A;

        // update heights of changed nodes:
        // update height of B before that of A, because B is now son of A
        updateNodeHeight(B);
        updateNodeHeight(A);
    }

    void rollLR(Node* C) {
        assert(C!= nullptr);
        Node* A = C->left;
        rollRR(A);
        rollLL(C);
    }


public:

    ~AvlTree() {
        // need to traverse in postorder and destroy each node
        destruct(root);
    }

    Node* find(const KeyType& key) const

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
        Node* newNode = new Node{key, value, parent};

        if (key < parent->key) {
            parent->left = newNode;
        }

        if (key > parent->key) {
            parent->right = newNode;
        }

        insertReBalance(newNode);
        return true;
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

        eraseReBalance(toDelete -> parent);
        delete toDelete;
        return true;
    }

    bool erase(const KeyType& key) // false if doesnt exist
    {
        Node* toDelete = findNode(key);
        return erase(toDelete);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }


};
