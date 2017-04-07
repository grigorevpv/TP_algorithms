#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T> void cSwap(T& t1, T& t2) {
    T tmp(t1);
    t1=t2;
    t2=tmp;
}

struct Element{
    int value;
    int index;

    Element( int v, int i ) : value(v), index(i) {};
    Element() : value(0), index(0) {};
};

class CHeap{
private:
    int numberOfElements;
    vector<Element> arr;
    int sizeOfWindow;

public:
    CHeap() : numberOfElements(0), sizeOfWindow(0) {};
    ~CHeap() {};

    friend istream& operator>> ( istream& , CHeap& );
    friend bool operator> (  Element& left,  Element& right );
    friend bool operator<= (  Element& left,  Element& right );
    int getMaximum();
    void insertWithPriority( Element element );
    Element peekAtNext( int first );
    int getSizeOfWindow(){ return sizeOfWindow; }
    vector<Element>::iterator getArrayAdr(){ return arr.begin(); }
    int getArraySize(){ return arr.size(); }
    void makeHeap();
    int getMax(){ return arr[0].value; }
    void siftDown( vector<Element>& , int );
    void siftUp( vector<Element>& , int );
    void copyArray( vector<Element>& mass, int size );
};

void CHeap::makeHeap() {
    for( int i = arr.size() / 2; i >= 0; --i ){
        siftDown( arr, i );
    }
}

istream& operator>>(istream& is, CHeap& heap){
    int value = 0;

    is >> heap.numberOfElements;
    assert( heap.numberOfElements >= 0 );

    int i = 0;
    while( i  < heap.numberOfElements && is >> value ){
        heap.arr.push_back( Element( value, i ) );
        i++;
    }

    cin >> heap.sizeOfWindow;
    assert( heap.sizeOfWindow >= 0 );

    return is;
}

bool operator> (  Element& left,  Element& right ) {
    return ( left.value > right.value );
}

bool operator<= (  Element& left,  Element& right ) {
    return ( left.value <= right.value );
}

/*void CHeap::siftUp(vector<Element>& arr, int index) {
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( arr[index] <= arr[parent] )
            return;
        cSwap( arr[index], arr[parent] );
        index = parent;
    }
}*/

void CHeap::siftDown(vector<Element> & arr, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    int largest = i;
    if( left < arr.size() && arr[left].value > arr[largest].value ){
        largest = left;
    }
    if( right < arr.size() && arr[right].value > arr[largest].value ){
        largest = right;
    }
    if( largest != i ){
        cSwap( arr[largest], arr[i] );
        siftDown( arr, largest );
    }

}

int CHeap::getMaximum(  ) {
    assert( arr.size() != 0 );

    int result = arr[0].value;

// Переносим последний элемент в корень.
    arr[0] = arr[arr.size() - 1];
    arr.pop_back();
// Вызываем SiftDown для корня.
    if( arr.size() != 0 ) {
        siftDown( arr, 0 );
    }
    return result;
}

void CHeap::insertWithPriority( Element element) {
    arr.push_back( element );
    siftUp( arr, arr.size() - 1 );
}

void CHeap::siftUp( vector<Element>& arr, int index ) {
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( arr[index] <= arr[parent] )
            return;
        cSwap( arr[index], arr[parent] );
        index = parent;
        }
}

Element CHeap::peekAtNext( int first ) {

    while ( arr[0].index < first ){
        arr[0] = arr[arr.size() - 1];
        arr.pop_back();
        siftDown( arr, 0 );
    }

    return arr[0];
}

void CHeap::copyArray(vector<Element> &mass, int size) {
    for( int i = 0; i < size; i++ ){
        arr.push_back( mass[i] );
    }
}

vector<int> caolculateMax( vector<Element>& heap, int sizeWindow ){
    vector<int> result;
    CHeap window;
    window.copyArray( heap, sizeWindow );
    window.makeHeap();
    result.push_back( window.getMax() );
    for( int i = sizeWindow; i < heap.size(); i++ ){
        window.insertWithPriority( heap[i] );
        result.push_back( window.peekAtNext( i - sizeWindow ).value );
    }
    return result;
}

int main() {
    vector<Element> arr;
    int count = 0;

    cin >> count;

    int i = 0;

    while( i < count ){
        int value = 0;
        cin >> value;
        arr.push_back( Element( value, i ) );
        i++;
    }

    int windowSize = 0;

    cin >> windowSize;

    vector<int> result = caolculateMax( arr, windowSize );

    for( auto k : result ){
        cout << k << " ";
    }

    return 0;
}

