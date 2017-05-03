/*
 Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то
узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
2_1. Выведите элементы в порядке in-order (слева направо).
 */

#include <iostream>
#include "vector"

struct CBinaryNode {
    int value;
    CBinaryNode *left;
    CBinaryNode *right;
    CBinaryNode *parent;

    CBinaryNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {};
};

class CBinaryTree {
private:
    CBinaryNode *root;
    int countNodes;
public:
    CBinaryTree() : root(nullptr), countNodes(0) {};
    ~CBinaryTree();
    void addNode(int val);

    void showTree();
};

void CBinaryTree::addNode(int val) {
    CBinaryNode *node = new CBinaryNode;
    node->value = val;
    countNodes++;

    if (!root) {
        root = node;
        return;
    }

    CBinaryNode *direction = root;

    while (direction) {
        if (val >= direction->value) {
            if (direction->right)
                direction = direction->right;
            else {
                node->parent = direction;
                direction->right = node;
                break;
            }
        } else {
            if (direction->left)
                direction = direction->left;
            else {
                node->parent = direction;
                direction->left = node;
                break;
            }
        }
    }
}

void CBinaryTree::showTree() {
    CBinaryNode *direction = root;
    CBinaryNode tmp;
    std::vector<CBinaryNode> stack;

    bool done = 0;

    while (!done) {
        /* Reach the left most tNode of the current tNode */
        if (direction != nullptr) {
            /* place pointer to a tree node on the stack before traversing
              the node's left subtree */
            stack.push_back(*direction);
            direction = direction->left;
        }

            /* backtrack from the empty subtree and visit the tNode
               at the top of the stack; however, if the stack is empty,
              you are done */
        else {
            if (stack.size() > 0) {
                tmp = stack.back();
                direction = &tmp;
                stack.pop_back();
                std::cout << direction->value << " ";

                /* we have visited the node and its left subtree.
                  Now, it's right subtree's turn */
                direction = direction->right;
            } else
                done = 1;
        }
    } /* end of while */
}

CBinaryTree::~CBinaryTree() {
    CBinaryNode* tmp = root;

    while( tmp ){
        if( tmp->left )
            tmp = tmp->left;
        else if( tmp->right )
            tmp = tmp->right;
        else{
            if( tmp->parent ) {
                CBinaryNode *parent = tmp->parent;
                delete tmp;
                tmp = parent;
                tmp->left = nullptr;
                tmp->right = nullptr;
            } else{
                delete tmp;
                break;
            }
        }
    }
}

int main() {
    CBinaryTree t;
    int value = 0;
    int count = 0;

    std::cin >> count;

    while (count--) {
        std::cin >> value;
        t.addNode(value);
    }

    t.showTree();
    return 0;
}