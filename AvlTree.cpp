#include <iostream>
#include <vector>
#include <algorithm> // for max, abs, sort
#include <cassert>
#include <cstdlib>   // for rand, srand
#include <ctime>     // for time
#include <map>       // used as "Ground Truth" for verification

#include "AvlTree.h" // Your header file

// ============================================================================
//                               VALIDATION LOGIC
// ============================================================================

// Helper to safely get height
template <typename Node>
int getHeight(Node* node) {
    return node ? node->height : -1;
}

// Deep validation of AVL invariants
template <typename Node>
bool validateAVLNodes(Node* node) {
    if (!node) return true;

    // 1. Verify Parent Pointer
    if (node->left && node->left->parent != node) {
        std::cerr << "CRITICAL: Left child of " << node->key << " has wrong parent pointer.\n";
        return false;
    }
    if (node->right && node->right->parent != node) {
        std::cerr << "CRITICAL: Right child of " << node->key << " has wrong parent pointer.\n";
        return false;
    }

    // 2. Verify BST Property
    if (node->left && node->left->key >= node->key) {
        std::cerr << "CRITICAL: BST Violation. Left " << node->left->key << " >= " << node->key << "\n";
        return false;
    }
    if (node->right && node->right->key <= node->key) {
        std::cerr << "CRITICAL: BST Violation. Right " << node->right->key << " <= " << node->key << "\n";
        return false;
    }

    // 3. Verify Height
    int hLeft = getHeight(node->left);
    int hRight = getHeight(node->right);
    int expectedHeight = 1 + std::max(hLeft, hRight);

    if (node->height != expectedHeight) {
        std::cerr << "CRITICAL: Height mismatch for " << node->key
                  << ". Stored: " << node->height << ", Calc: " << expectedHeight << "\n";
        return false;
    }

    // 4. Verify Balance Factor
    int bf = hLeft - hRight;
    if (std::abs(bf) > 1) {
        std::cerr << "CRITICAL: Node " << node->key << " is unbalanced. BF: " << bf << "\n";
        return false;
    }

    return validateAVLNodes(node->left) && validateAVLNodes(node->right);
}

template <typename Tree>
void check(const Tree& tree) {
    if (tree.root) {
        assert(tree.root->parent == nullptr); // Root must have no parent
    }
    if (!validateAVLNodes(tree.root)) {
        std::cerr << "Validation Failed! Aborting.\n";
        std::abort();
    }
}

// ============================================================================
//                               SPECIFIC TESTS
// ============================================================================

void testEmptyTree() {
    std::cout << "[Test] Empty Tree Operations... ";
    AvlTree<int, int> tree;
    assert(tree.root == nullptr);
    assert(tree.erase(10) == false); // Erase from empty
    assert(tree.find(10) == nullptr); // Find in empty
    check(tree);
    std::cout << "OK\n";
}

void testSingleElement() {
    std::cout << "[Test] Single Element Lifecycle... ";
    AvlTree<int, int> tree;

    // Insert
    assert(tree.insert(10, 100) == true);
    assert(tree.root != nullptr);
    assert(tree.root->key == 10);
    assert(tree.root->height == 0);
    check(tree);

    // Duplicate Insert
    assert(tree.insert(10, 200) == false); // Should fail

    // Find
    assert(tree.find(10) != nullptr);
    assert(tree.find(10)->value == 100);

    // Erase
    assert(tree.erase(10) == true);
    assert(tree.root == nullptr);
    check(tree);
    std::cout << "OK\n";
}

void testLLCase() {
    std::cout << "[Test] Rotation LL (Left-Left)... ";
    AvlTree<int, int> tree;
    //     30
    //    /
    //   20
    //  /
    // 10
    tree.insert(30, 0);
    tree.insert(20, 0);
    tree.insert(10, 0); // Triggers LL rotation

    check(tree);
    // Root should become 20
    assert(tree.root->key == 20);
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    assert(tree.root->height == 1);
    std::cout << "OK\n";
}

void testRRCase() {
    std::cout << "[Test] Rotation RR (Right-Right)... ";
    AvlTree<int, int> tree;
    // 10
    //   \
    //    20
    //      \
    //       30
    tree.insert(10, 0);
    tree.insert(20, 0);
    tree.insert(30, 0); // Triggers RR rotation

    check(tree);
    // Root should become 20
    assert(tree.root->key == 20);
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    std::cout << "OK\n";
}

void testLRCase() {
    std::cout << "[Test] Rotation LR (Left-Right)... ";
    AvlTree<int, int> tree;
    //   30
    //   /
    // 10
    //   \
    //    20
    tree.insert(30, 0);
    tree.insert(10, 0);
    tree.insert(20, 0); // Triggers LR

    check(tree);
    assert(tree.root->key == 20);
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    std::cout << "OK\n";
}

void testRLCase() {
    std::cout << "[Test] Rotation RL (Right-Left)... ";
    AvlTree<int, int> tree;
    // 10
    //   \
    //    30
    //    /
    //   20
    tree.insert(10, 0);
    tree.insert(30, 0);
    tree.insert(20, 0); // Triggers RL

    check(tree);
    assert(tree.root->key == 20);
    assert(tree.root->left->key == 10);
    assert(tree.root->right->key == 30);
    std::cout << "OK\n";
}

void testZigZagGrowth() {
    std::cout << "[Test] Zig-Zag Growth Patterns... ";
    AvlTree<int, int> tree;
    // Insert: 50, 20, 80, 10, 30, 70, 90, 25, 28
    // This forces deep updates
    int keys[] = {50, 20, 80, 10, 30, 70, 90, 25, 28};
    for (int k : keys) {
        tree.insert(k, 0);
        check(tree);
    }
    assert(tree.find(28) != nullptr);
    std::cout << "OK\n";
}

void testDeleteLeaf() {
    std::cout << "[Test] Delete Leaf... ";
    AvlTree<int, int> tree;
    tree.insert(10, 0);
    tree.insert(5, 0); // Left leaf
    tree.insert(15, 0); // Right leaf

    tree.erase(5);
    check(tree);
    assert(tree.find(5) == nullptr);
    assert(tree.root->left == nullptr);

    tree.erase(15);
    check(tree);
    assert(tree.find(15) == nullptr);
    assert(tree.root->right == nullptr);
    std::cout << "OK\n";
}

void testDeleteOneChild() {
    std::cout << "[Test] Delete Node with 1 Child... ";
    AvlTree<int, int> tree;
    //      20
    //     /
    //   10
    //     \
    //      15
    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(15, 0); // Double rotation happens here during insert likely

    // Ensure structure is maintained before delete
    check(tree);

    // Erase 10 (which should have child 15, or after rotation 15 is root of subtree)
    // Depending on rotation, structure might be 15 (left 10, right 20).
    // Let's force a simpler one-child case without rotation interference:
    AvlTree<int, int> t2;
    t2.insert(50, 0);
    t2.insert(40, 0);
    t2.insert(45, 0); // Balanced now: 45 (L:40, R:50)
    t2.insert(30, 0);
    // 45
    // / \
    //40  50
    // /
    //30

    t2.erase(40); // 40 has one child (30)
    check(t2);
    assert(t2.find(40) == nullptr);
    assert(t2.find(30) != nullptr);
    // 30 should now be child of 45
    assert(t2.root->left->key == 30);
    std::cout << "OK\n";
}

void testDeleteTwoChildren() {
    std::cout << "[Test] Delete Node with 2 Children... ";
    AvlTree<int, int> tree;
    //      20
    //     /  \
    //   10    30
    //        /  \
    //       25   35
    tree.insert(20, 0);
    tree.insert(10, 0);
    tree.insert(30, 0);
    tree.insert(25, 0);
    tree.insert(35, 0);

    // Erase 30. Successor is 35 (or 25 depending on impl, usually min of right subtree).
    tree.erase(30);
    check(tree);

    assert(tree.find(30) == nullptr);
    // 25 and 35 should still be in the tree
    assert(tree.find(25) != nullptr);
    assert(tree.find(35) != nullptr);
    std::cout << "OK\n";
}

void testDeleteRoot() {
    std::cout << "[Test] Delete Root Repeatedly... ";
    AvlTree<int, int> tree;
    tree.insert(10, 0);
    tree.insert(20, 0);
    tree.insert(5, 0);

    // Delete root (10)
    tree.erase(10);
    check(tree);
    assert(tree.find(10) == nullptr);
    // New root should be 20 or 5

    // Delete new root
    int rootKey = tree.root->key;
    tree.erase(rootKey);
    check(tree);

    // Delete last one
    rootKey = tree.root->key;
    tree.erase(rootKey);
    check(tree);
    assert(tree.root == nullptr);
    std::cout << "OK\n";
}

// ============================================================================
//                               FUZZ TESTING (STRESS)
// ============================================================================

void testFuzzWithOracle() {
    std::cout << "[Test] Fuzz Testing (AVL vs std::map)... \n";
    AvlTree<int, int> myTree;
    std::map<int, int> oracle; // The ground truth
    std::vector<int> keys;     // Keep track of keys for random selection

    int OPERATIONS = 10000;

    for (int i = 0; i < OPERATIONS; ++i) {
        int op = rand() % 100;
        int key = rand() % 5000; // Small range to force collisions

        if (op < 60) {
            // --- INSERT (60% chance) ---
            bool myRes = myTree.insert(key, key);
            auto oracleRes = oracle.insert({key, key});

            if (myRes != oracleRes.second) {
                std::cerr << "Mismatch on Insert " << key << "! AVL:" << myRes << " Map:" << oracleRes.second << "\n";
                std::abort();
            }
            if (myRes) keys.push_back(key);
        }
        else if (op < 90) {
            // --- ERASE (30% chance) ---
            if (keys.empty()) continue;
            int randIdx = rand() % keys.size();
            int targetKey = keys[randIdx];

            bool myRes = myTree.erase(targetKey);
            size_t oracleRes = oracle.erase(targetKey);

            if (myRes != (oracleRes > 0)) {
                std::cerr << "Mismatch on Erase " << targetKey << "! AVL:" << myRes << " Map:" << oracleRes << "\n";
                std::abort();
            }

            // Remove from keys vector (swap with back and pop is O(1))
            keys[randIdx] = keys.back();
            keys.pop_back();
        }
        else {
            // --- FIND (10% chance) ---
            int searchKey = rand() % 5000;
            auto myNode = myTree.find(searchKey);
            auto oracleIt = oracle.find(searchKey);

            bool myFound = (myNode != nullptr);
            bool oracleFound = (oracleIt != oracle.end());

            if (myFound != oracleFound) {
                std::cerr << "Mismatch on Find " << searchKey << "! AVL:" << myFound << " Map:" << oracleFound << "\n";
                std::abort();
            }
        }

        // Validate invariants periodically (it's expensive)
        if (i % 500 == 0) {
            check(myTree);
            // Verify root hasn't drifted
            if (myTree.root) assert(myTree.root->parent == nullptr);
        }
    }

    // Final check
    check(myTree);

    // Check size match? (Assuming you don't have a size function, we skip)
    std::cout << "Completed " << OPERATIONS << " random operations successfully.\n";
}

void testAscendingDescending() {
    std::cout << "[Test] Worst Case Insert (Sorted Data)... ";
    AvlTree<int, int> t1;
    // 1..100
    for(int i=0; i<100; i++) {
        t1.insert(i, 0);
        check(t1); // Validate every step
    }
    // Height should be logarithmic ~7 (log2(100) = 6.6)
    int h = getHeight(t1.root);
    assert(h <= 8);

    AvlTree<int, int> t2;
    // 100..1
    for(int i=100; i>0; i--) {
        t2.insert(i, 0);
        check(t2);
    }
    h = getHeight(t2.root);
    assert(h <= 8);
    std::cout << "OK\n";
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    std::cout << "==========================================\n";
    std::cout << "      MASSIVE AVL TREE TEST SUITE         \n";
    std::cout << "==========================================\n";

    testEmptyTree();
    testSingleElement();

    // Rotation Logic
    testLLCase();
    testRRCase();
    testLRCase();
    testRLCase();

    // Structural Tests
    testZigZagGrowth();
    testAscendingDescending();

    // Deletion Logic
    testDeleteLeaf();
    testDeleteOneChild();
    testDeleteTwoChildren();
    testDeleteRoot();

    // Stress Test
    testFuzzWithOracle();

    std::cout << "\nALL TESTS PASSED! YOUR TREE IS ROCK SOLID.\n";
    return 0;
}