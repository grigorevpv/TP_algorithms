#include <iostream>
#include <limits>
#include <vector>


int MAX_VALUE = std::numeric_limits<int>::max();

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
    void addRoot( int val, int priority );
    void split(CTreapNode *root, CTreapNode* &left, CTreapNode* &right, int val);
    void merge(CTreapNode* &root, CTreapNode *left, CTreapNode *right);
    void insert(CTreapNode* &root, int key, int rand);
    CTreapNode* getRoot( ){ return root; };
    CTreapNode* getRootLeft( ){ return root->left; };
    CTreapNode* getRootRight( ){ return root->right; };

};

void CTreap::addRoot( int val, int priority ) {
    root = new CTreapNode( val, priority );
    countNodes++;
}

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

void CTreap::merge(CTreapNode* &root, CTreapNode *left, CTreapNode *right) {
    if (left == nullptr || right == nullptr)
    {
        root = right == nullptr ? left : right;
        return;
    }
    if (left->priority > right->priority)
    {
        merge(left->right, left->right, right);
        root = left;
    }
    else
    {
        merge(right->left, left, right->left);
        root = right;
    }
}

void CTreap::insert(CTreapNode* &root, int key, int rand) {
    CTreapNode* node = new CTreapNode( key, rand );
    CTreapNode* left = nullptr;
    CTreapNode* right = nullptr;
    split( root, left, right, node->key );
    merge( root, left, right );
}

int findPositinInVector( std::vector<CTreapNode> & arr, int val ){
    int position = 0;
    for( int i = 0; i < arr.size(); i++ ){
        position = val == arr[i].priority ? i : 0;
        if( position )
            return position;
    }
    return -1;
}


int main() {
    srand(MAX_VALUE - 1);
    std::vector<CTreapNode> arr;
    CTreap t;
    int count = 0;
    int value = 0, priority = 0;

    std::cin >> count;

    int i = count;
    int maxPriority = 0;
    while( i-- ) {
        std::cin >> value >> priority;
        arr.push_back( CTreapNode( value, priority ) );
        maxPriority = maxPriority < priority ? priority : maxPriority;
    }

    int position = findPositinInVector( arr, maxPriority );
    std::swap<CTreapNode>( arr[position], arr[arr.size()-1] );

    t.addRoot( arr[arr.size() - 1].key, arr[arr.size() - 1].priority );
    arr.pop_back();

    for( int i = 0; i < arr.size(); i++ ){
        t.insert( t.root, arr[i].key, arr[i].priority );
    }

    return 0;
}