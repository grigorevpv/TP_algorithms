#include <iostream>
#include <vector>

using namespace std;

//template <class T>
struct Entry{
    string val;
    int key;

    Entry() : val("0"), key(0) {};
    Entry( string& v, int k ) : val(v), key(k) {};
};

//template <class T>
class HashMap{
private:
    vector<Entry> arr;
    int arrSize;
    int elemInArr;
    int limit;

public:
    bool Has( string& key ) const;
    void Add( string& key );
    bool Delete( string& key );
    HashMap( int );
    int Hash( string& key, int size );
    int Hash2( int key );
    void RebuildHashMap();
};

//template <class T>
HashMap::HashMap( int size ) {
    arr.resize(size);
    elemInArr = 0;
    arrSize = size;
    cout << "arr.size = " << arr.size() << endl;
    limit = arrSize * 0.75;        // 3/4 от размера массива
    cout << "limit = " << limit << endl;
}

//template <class T>
bool HashMap::Has( string &key ) const {
    return false;
}

//template <class T>
int HashMap::Hash( string &key, int size ) {
    int hash = 0;
    int a = 3;                      // константа, которая является взаимно простым числом с размером массива
    for( int i = 0; i < size; i++ ){
        hash = ( hash * a + key[i] ) % arrSize;
    }
    return hash;
}

//template <class T>
void HashMap::Add( string &key ) {
    Entry ent = Entry( key, Hash( key, key.length() ) );
    int index = ent.key;

    if( elemInArr < limit ){
        if( arr[index].key == 0 || arr[index].val == "0" ){                  // костыли ( убрать в конечной реализации)
            arr[index] = ent;
            cout << "index = " << index << endl;
        }
        else {
            for( int i = 0; i < arrSize; i++ ){
                index = ( Hash( key, key.length() ) + i * Hash2( Hash( key, key.length() ) ) ) % arrSize;
                if( arr[index].val == "0" ){
                    arr[index] = ent;
                }
                cout << "index(h2) = " << index << endl;
            }
        }
    }
    else {
        cout << "rebuild ---------------------" << endl;
        RebuildHashMap();
    }
    elemInArr++;
}

//template <class T>
int HashMap::Hash2( int key ) {             // данная функция оправдана только тогда, когда значение размера массива кратно 2
    return ( key % ( arrSize - 1 ) ) + 1;
}

//template <class T>
void HashMap::RebuildHashMap() {
    vector<Entry> tmp = arr;
    elemInArr = 0;
    arrSize *= 2;
    limit = 0.75 * arrSize;
    cout << "limit = " << limit << endl;
    vector<Entry>( arrSize ).swap( arr );
    for( int i = 0; i < arrSize / 2; i++ ){
        if( tmp[i].val != "0" ){
            /*Entry ent = Entry( tmp[i].val, Hash( tmp[i].val, tmp[i].val.len() ) );
            arr[ent.key] = ent;*/
            this->Add( tmp[i].val );
        }
    }
}

int main() {
    HashMap h( 8 );
//    string s = "sdf13";
//    h.Add(s);
    for( int i = 1; i < 44; i++ ){
        string s = "sdf" + to_string(i);
        cout << " s = " << s << endl;
        h.Add(s);
    }
    return 0;
}