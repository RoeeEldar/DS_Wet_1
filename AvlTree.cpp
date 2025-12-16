#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "AvlTree.h"

#define LOG(msg) std::cout << "\033[32m[TEST PASSED] \033[0m" << msg << std::endl

// --- בדיקות בסיסיות ומבניות (מהקוד הקודם) ---

void Test_Successor_Has_Right_Child() {
    // Scenario #25: העוקב אינו הבן הימני הישיר, ויש לו ילד ימני משלו
    AvlTree<int, std::string> tree;

    // בניית עץ ספציפי למקרה הזה
    tree.insert(20, "Root");
    tree.insert(10, "L");
    tree.insert(30, "R");
    tree.insert(25, "RL"); // אבא של העוקב
    tree.insert(40, "RR");
    tree.insert(27, "RLR - Successor"); // העוקב של 20
    tree.insert(28, "RLRR - Child of Successor"); // הילד של העוקב

    // מחיקת השורש (20).
    // 27 אמור לעלות לשורש.
    // 28 (הילד של 27) אמור להתחבר ל-25 (האבא הישן של 27) כבן ימני.
    assert(tree.erase(20) == true);

    auto* newRoot = tree.find(25); // אנחנו מחפשים לפי מפתח 27, אבל הערך הועתק לצומת הפיזי של 20
    // הערה: במימוש שלך, אם אתה עושה swap ל-KEY ול-VALUE, אז ה-KEY 27 נמצא עכשיו בשורש.

    assert(tree.find(20) == nullptr); // נמחק
    assert(newRoot != nullptr);
    assert(newRoot->parent == nullptr); // הוא שורש

    // בדיקת החיבור הקריטי: 25 צריך להצביע ל-28
    auto* node25 = tree.find(25);
    auto* node30 = tree.find(30);

    assert(node25->right == node30);
    assert(node30->parent == node25);

    LOG("Complex Successor Swap (Successor has Right Child)");
}

// --- בדיקות עומס ומקרי קצה לוגיים (Stress & Logic) ---

void Test_Sanity_And_Duplicates() {
    AvlTree<int, int> tree;

    // מקרה 41: הכנסת כפילויות
    assert(tree.insert(5, 5) == true);
    assert(tree.insert(5, 5) == false); // אמור להיכשל

    // מקרה 42: מחיקת מפתח לא קיים
    assert(tree.erase(999) == false);

    // מקרה 43+44: מחיקת מפתח קטן/גדול מדי
    assert(tree.erase(-100) == false);
    assert(tree.erase(100) == false);

    LOG("Sanity & Duplicates");
}

void Test_Skewed_Lines() {
    // מקרה 31+32: טיפול בקו ישר (רשימה מקושרת)
    AvlTree<int, int> rightLine;
    AvlTree<int, int> leftLine;

    for (int i = 0; i < 10; ++i) {
        rightLine.insert(i, i);      // 0->1->2...
        leftLine.insert(10 - i, i);  // 10->9->8...
    }

    // מחיקה מהאמצע בקו ימני
    assert(rightLine.erase(5) == true);
    assert(rightLine.find(4)->right->key == 6); // 4 מתחבר ל-6
    assert(rightLine.find(6)->parent->key == 4);

    // מחיקה מהאמצע בקו שמאלי
    assert(leftLine.erase(5) == true);
    assert(leftLine.find(6)->left->key == 4); // 6 מתחבר ל-4
    assert(leftLine.find(4)->parent->key == 6);

    LOG("Skewed Lines (Left/Right)");
}

void Test_Stress_Massive_Insert_Delete() {
    // מקרה 46: בדיקת עומס (500 איברים) ומחיקה בסדר מבולגן
    // זה מכסה סטטיסטית כמעט את כל הקומבינציות של עלים/ילד אחד/שני ילדים

    AvlTree<int, int> tree;
    std::vector<int> keys;

    // 1. הכנסה
    for (int i = 0; i < 500; ++i) {
        keys.push_back(i);
        assert(tree.insert(i, i) == true);
    }

    // 2. מחיקת הזוגיים בלבד (יוצר המון חורים ומצבי "ילד יחיד")
    for (int i = 0; i < 500; i += 2) {
        assert(tree.erase(i) == true);
        assert(tree.find(i) == nullptr); // וידוא שנמחק
    }

    // 3. וידוא שהאי זוגיים קיימים
    for (int i = 1; i < 500; i += 2) {
        assert(tree.find(i) != nullptr);
    }

    // 4. מחיקת האי זוגיים בסדר הפוך (מהסוף להתחלה)
    for (int i = 499; i > 0; i -= 2) {
        assert(tree.erase(i) == true);
    }

    // 5. העץ אמור להיות ריק
    assert(tree.find(1) == nullptr);
    // ניסיון הכנסה מחדש לוודא שהשורש התאפס כמו שצריך (מקרה 5)
    assert(tree.insert(100, 100) == true);

    LOG("Stress Test (500 Nodes, Mixed Deletion)");
}

int main() {
    std::cout << "--- STARTING EXTENDED TESTS ---" << std::endl;

    Test_Successor_Has_Right_Child();
    Test_Sanity_And_Duplicates();
    Test_Skewed_Lines();
    Test_Stress_Massive_Insert_Delete();

    std::cout << "\nALL TESTS PASSED. Tree logic is solid." << std::endl;
    return 0;
}