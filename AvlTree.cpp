#include <iostream>
#include <cassert>
#include <algorithm> // For std::max
#include "AvlTree.h"

#define LOG(msg) std::cout << "[TEST] " << msg << std::endl

void Test_Height_SimpleLine() {
    LOG("Running Height: Simple Line (0->1->2)...");
    AvlTree<int, int> tree;

    // 1. Insert Root
    tree.insert(10, 10);
    auto n10 = tree.find(10);
    assert(n10->height == 0); // Leaf height is 0

    // 2. Insert Child (10 -> 20)
    tree.insert(20, 20);
    auto n20 = tree.find(20);

    assert(n20->height == 0); // New leaf
    assert(n10->height == 1); // Root grew

    // 3. Insert Grandchild (10 -> 20 -> 30)
    tree.insert(30, 30);
    auto n30 = tree.find(30);

    assert(n30->height == 0);
    assert(n20->height == 1);
    assert(n10->height == 2);

    LOG("Height: Simple Line Passed!");
}

void Test_Height_Branching_Logic() {
    LOG("Running Height: Branching (The Logic Check)...");
    AvlTree<int, int> tree;

    // Create a tree with a long right arm:
    //      10 (h=2)
    //        \
    //         20 (h=1)
    //           \
    //            30 (h=0)
    tree.insert(10, 10);
    tree.insert(20, 20);
    tree.insert(30, 30);

    assert(tree.find(10)->height == 2);

    // Now insert to the LEFT of 10.
    // This creates a path of length 1 on the left.
    //      10
    //     /  \
    //    5    20...
    //
    // CRITICAL: The height of 10 should STILL be 2,
    // because the right side (length 2) is still longer than the left side (length 1).

    tree.insert(5, 5);

    auto root = tree.find(10);
    auto left = tree.find(5);
    auto right = tree.find(20);

    assert(left->height == 0);

    // If your logic just does ++height for all parents, this will fail (it will be 3).
    // In AVL, height = max(left_height, right_height) + 1
    if (root->height == 3) {
        std::cout << "\033[31m[WARNING] Logic Error: Root height increased to 3, but longest path is still 2.\033[0m" << std::endl;
        std::cout << "Your increaseHeight() blindly adds +1 to ancestors." << std::endl;
        std::cout << "It should be: node->height = max(left, right) + 1" << std::endl;
    } else {
        assert(root->height == 2);
        LOG("Height: Branching Logic Passed!");
    }
}

void Test_Height_Erase_Leaf() {
    LOG("Running Height: Erase Leaf...");
    AvlTree<int, int> tree;

    //      10 (h=1)
    //     /
    //    5 (h=0)
    tree.insert(10, 10);
    tree.insert(5, 5);

    assert(tree.find(10)->height == 1);

    // Delete 5. 10 becomes a leaf (h=0).
    tree.erase(5);

    assert(tree.find(5) == nullptr);
    assert(tree.find(10)->height == 0);

    LOG("Height: Erase Leaf Passed!");
}

int main() {
    Test_Height_SimpleLine();
    Test_Height_Branching_Logic();
    Test_Height_Erase_Leaf();

    std::cout << "\nTests Finished." << std::endl;
    return 0;
}