/*
 10
5 11
18 8
25 7
50 12
30 30
15 15
20 10
22 5
40 20
45 9

4
7 10
14 4
13 8
6 3
 */

#include <iostream>
#include <limits>
#include <vector>


//////////////////////////////////////////////////
struct CBinaryNode {
    int value;
    CBinaryNode *left;
    CBinaryNode *right;
    CBinaryNode *parent;

    CBinaryNode() : value(0), left(nullptr), right(nullptr), parent(nullptr) {};
};

class CBinaryTree {
public:
    CBinaryNode *root;
    int countNodes;
public:
    CBinaryTree() : root(nullptr), countNodes(0) {};

    void addNode(int val);
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
//////////////////////////////////////////////////


struct CTreapNode {
    int key;
    int priority;
    CTreapNode *left;
    CTreapNode *right;

    CTreapNode() : key(0), priority(0), left(nullptr), right(nullptr) {}

    CTreapNode( int newKey, int rand ) : key(newKey), priority(rand), left(nullptr), right(nullptr) {}
};

class CTreap {
public:
    CTreapNode *root;
    int countNodes;
public:
    CTreap() : root(nullptr), countNodes(0) {};
    void split(CTreapNode *root, CTreapNode* &left, CTreapNode* &right, int val);
    CTreapNode* merge( CTreapNode *left, CTreapNode *right );
    void insert(CTreapNode* &root, int key, int rand);
};

void CTreap::split(CTreapNode *root, CTreapNode* &left, CTreapNode* &right, int val) {
    if( !root ){
        left = right = nullptr;
        return;
    }

    if( root->key < val ){
        split( root->right, root->right, right, val );
        left = root;
    } else {
        split( root->left, left, root->left, val );
        right = root;
    }
}

CTreapNode* CTreap::merge( CTreapNode *left, CTreapNode *right ) {
    if (left == NULL || right == NULL) {
        return (left == NULL) ? right : left;
    }

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

void CTreap::insert(CTreapNode* &root, int key, int rand) {
    CTreapNode* node = new CTreapNode( key, rand );
    CTreapNode* left = nullptr;
    CTreapNode* right = nullptr;
    split( root, left, right, node->key );
    root = merge( merge( left, node ), right );
}

template <typename node_t>
int depth_recursive(node_t *node, int &max_depth, int current_depth = 1) {
    if (node == NULL) return 0;

    if (current_depth > max_depth) max_depth = current_depth;
    if (node->left != NULL) depth_recursive(node->left, max_depth, current_depth + 1);
    if (node->right != NULL) depth_recursive(node->right, max_depth, current_depth + 1);

    return max_depth;
}



int main() {
    CTreap t;
    CBinaryTree tree;
    int count = 0;
    int value = 0, priority = 0;

    std::cin >> count;

    int i = count;
    while( i-- ) {
        std::cin >> value >> priority;
        t.insert( t.root, value, priority );
        tree.addNode( value );
    }

    int depth1 = 0;
    int current_depth1 = 1;
    int depth2 = 0;
    int current_depth2 = 1;
    std::cout << depth_recursive( tree.root, depth2, current_depth2 ) - depth_recursive( t.root, depth1, current_depth1 );

    return 0;
}