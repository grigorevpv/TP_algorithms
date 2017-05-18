/*
Тесты:

 5
1 100
1 200
1 50
2 1
1 150

 4
2 1
2 0
2 0
1 1

 6
1 5
1 3
1 2
1 1
2 0
1 4


 6
1 5
1 3
1 2
1 1
1 0
1 -1


 6
1 1
1 2
1 3
1 4
2 2
1 6

 10
 1 20
 1 30
 1 10
 1 50
 2 2
 2 1
 1 40
 1 30
 2 0
 1 50

 3
 1 1
 2 0
 1 1

9
 1 180
 1 15
 1 200
 1 60
 1 35
 1 90
 1 8
 1 600
 1 4000

 13
 1 180
 1 15
 1 200
 2 1
 1 60
 1 35
 2 1
 1 90
 1 8
 2 3
 1 600
 1 4000
 2 0

 10
 1 10
 1 20
 2 1
 1 30
 1 40
 2 2
 1 50
 1 60
 2 4
 2 3
 */

#include <iostream>
#include <stack>
#include <vector>

struct node{
    int key;
    int height;
    int position;
    int nodes;
    node* left;
    node* right;

    node( int k, int pos ): key( k ), height( 1 ), nodes( 1 ), position( pos ), left( nullptr ), right( nullptr ) {}
};

int height( node* p );
int nodes( node* p );
int bFactor( node* p );
void fixHeight( node* p );
void fixNodes( node* p );
void increasePosition( node *p );
void decreasPosition( node *p );
node* rightRotation( node* p );
node* leftRotation( node* q );
node* balanceTree( node* p );
node* insert( int& pos, node* p, int k );
node* findMinNode( node *p );
node* removeMinNode( node* p );
node* findMinNode(node *p);
node* findMinNode(node *p);


// получение значения высоты
int height( node *p ) {
    return p?p->height:0;
}

int nodes( node* p ){
    return p?p->nodes:0;
}

// Вычисление баланса сначало значениям в сыновьях
int bFactor( node *p ) {
    return height( p->right ) - height( p->left );
}

// Восстановление высоты в узле
void fixHeight( node *p ) {
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

// функция, восстанавливает значение колличества узлов-сыновей
void fixNodes( node* p ){
    int nl = nodes( p->left );
    int nr = nodes( p->right );
    p->nodes = nl + nr + 1;
}

// Простой правый поворот
node *rightRotation( node *p ) {
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixNodes( p );
    fixNodes( q );
    fixHeight( p );
    fixHeight( q );
    return q;
}

// Простой левый поворот
node *leftRotation( node *q ) {
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixNodes( q );
    fixNodes( p );
    fixHeight( q );
    fixHeight( p );
    return p;
}

node *balanceTree( node *p ) {

    fixHeight( p );
    if( bFactor( p ) == 2 ) {
        if ( bFactor(p->right) < 0 )
            p->right = rightRotation(p->right);
        return leftRotation( p );
    }

    else if( bFactor( p ) == -2 ) {
        if( bFactor( p->left ) > 0 )
            p->left = leftRotation( p->left );
        return rightRotation( p );
    }

    return p;
}

// рекурсивная вставка нового узла
node *insertRecursion(int& pos, node *p, int k) {
    // если узел не существует, то создаем
    if( !p ) {
        return new node( k, pos );
    }

    ++( p->nodes );

    if (k < p->key) {
        pos += nodes( p->right ) + 1;
        p->left = insertRecursion( pos, p->left, k );
    } else {
        p->right = insertRecursion( pos, p->right, k );
    }

    return balanceTree( p );
}

// Поиск минимального узла
node* findMinNode(node *p) {
    return ( p->left == nullptr ) ? p : findMinNode(p->left);
}

// удаление минимального элемента
node* removeMin(node *p) {
    if (!p->left ) {
        return p->right;
    }

    p->left = removeMin(p->left);
    --( p->nodes );

    return balanceTree(p);
}

// удаление минимального элемента
node* removeMin2(node *p, node*& minNode) {
    if (!p->left ) {
        minNode = p;
        return p->right;
    }

    p->left = removeMin2(p->left, minNode);
    --( p->nodes );

    return balanceTree(p);
}



// Увеличение значения позиции у всех дочерних элементов
void increasePosition(node *p){
    if( p->left ){
        increasePosition(p->left);
    }
    if( p->right ){
        increasePosition(p->right);
    }
    p->position++;
    return;
}

// Уменьшение значения позиции у всех дочерних элементов
void decreasPosition(node *p){
    if( p->left ){
        decreasPosition(p->left);
    }
    if( p->right ){
        decreasPosition(p->right);
    }
    p->position--;
    return;
}


node* removeNode(node *p, int position) {
    if (p == NULL) return NULL;
    if (position >= p->nodes) return p;

    int current = 0;
    std::stack<node *> stack;

    while (true) {
        int nodes_right = nodes(p->right);

        if (position - current > nodes_right) {
            stack.push(p);
            p = p->left;
            current += nodes_right + 1;
        } else if (position - current < nodes_right) {
            if (p->right != NULL) {
                stack.push(p);
                p = p->right;
            } else {
                break;
            }
        } else {
            node *left = p->left;
            node *right = p->right;
            int key = p->key;

            if (right == NULL) {
                if (left == NULL) {
                    if (!stack.empty()) {
                        p = stack.top();
                        stack.pop();

                        if (p->key > key) {
                            p->left = NULL;
                        } else {
                            p->right = NULL;
                        }

                        --p->nodes;
                    } else {
                        return NULL;
                    }
                } else {
                    p = left;
                }
            } else {
                node* min = nullptr;
                p->right = removeMin2( right, min );
                p->key = min->key;
                p->left = left;
                fixNodes(p);
                p = balanceTree(p);
            }

            break;
        }
    }

    while (!stack.empty()) {
        node *node = stack.top();
        --node->nodes;

        if (node->key > p->key) {
            node->left = p;
        } else {
            node->right = p;
        }

        p = balanceTree(node);
        stack.pop();
    }

    return p;
}

int main() {
    std::vector<int> result;
    int count = 0;
    int command = 0;
    int value = 0;
    node* root = nullptr;

    std::cin >> count;

    for( int i = 0; i < count; i++ ){
        int pos = 0;
        std::cin >> command >> value;

        switch ( command ){
            case 1: {
                root = insertRecursion(pos, root, value);
                result.push_back( pos );
                break;
            }
            case 2: {
                root = removeNode(root, value);
                break;
            }
            default:
                break;
        }

    }

    for( auto res : result ){
        std::cout << res << std::endl;
    }

    return 0;
}
