/*
 Дано число N < 10^6 и последовательность целых чисел из [-2^31..2^31] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то
узел K добавляется в правое поддерево root; иначе в левое поддерево root.
Рекурсия запрещена.
2_1. Выведите элементы в порядке in-order (слева направо).
 */

#include <iostream>
#include <raseapif.h>

struct CBinaryNode{
    int value;
    CBinaryNode* left;
    CBinaryNode* right;
    CBinaryNode* parent;

    CBinaryNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {}
};

class CBinaryTree{
private:
    CBinaryNode* root;
    int countNodes;
public:
    CBinaryTree() : root(nullptr), countNodes(0) {};
    void addNode( int val );
    void showTree( );
};

void CBinaryTree::addNode(int val) {
    CBinaryNode* node = new CBinaryNode;
    node->value = val;

    if( !root ) {
        root = node;
        return;
    }

    CBinaryNode* direction = root;

    while( direction ){
        if( val > direction->value ) {
            if( direction->right )
                direction = direction->right;
            else{
                node->parent = direction;
                direction->right = node;
            }
        } else{
            if( direction->left )
                direction = direction->left;
            else{
                node->parent = direction;
                direction->left = node;
            }
        }
    }
}

void CBinaryTree::showTree() {

}


int main() {
    CBinaryTree t;
    t.addNode( 1 );
    t.addNode( 3 );
    t.addNode( 0 );
    return 0;
}