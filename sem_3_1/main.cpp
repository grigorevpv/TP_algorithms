#include <iostream>
#include <vector>

using namespace std;

enum EntryStatus{
    empty, deleted, filled
};

struct Entry{
    string key;
    EntryStatus status;

    Entry() : key(""), status(empty) {};
    Entry( string& k ) : key(k), status(filled) {};
};

class HashMap{
private:
    vector<Entry> arr;            // хеш-таблица
    int arrSize;                  // размер хеш-таблицы
    int elemInArr;                // количество эл-тов в хеш-таблице
    int limit;                    // предльное значения заполнения, равное 0,75*arrSize

public:
    bool Has( const string& key, int& position ) const;
    bool Add( string& key );
    bool Delete( string& key );
    HashMap( int );
    int Hash( const string& key, int size ) const;
    int Hash2( int key ) const;
    void RebuildHashMap();
};

int HashMap::Hash(const string &key, int size) const {
    int hash = 0;
    int a = 3;                      // константа, которая является взаимно простым числом с размером массива
    for( int i = 0; i < size; i++ ){
        hash = ( hash * a + key[i] ) % arrSize;
    }
    return hash;
}

int HashMap::Hash2( int key) const {
    return ( key % ( arrSize - 1 ) ) + 1;
}

HashMap::HashMap( int size ) {
    arr.resize(size);
    elemInArr = 0;
    arrSize = size;
    cout << "arr.size = " << arr.size() << endl;
    limit = arrSize * 0.75;        // 3/4 от размера массива
    cout << "limit = " << limit << endl;
}

bool HashMap::Has( const string &key, int& position ) const {
    for( int i = 0; i < arrSize; i++ ){
        int index = ( Hash( key, key.length() ) + i * Hash2( Hash( key, key.length() ) ) ) % arrSize;
        if( arr[index].status == empty ){
            if( position == -1 ){           // назначаем позицию только в том случае, если до этого не встречалась ячейка с удаленным элементом
                position = index;
            }
            return false;
        }
        if( arr[index].status == deleted ){
            position = index;
            continue;
        }
        if( arr[index].status == filled && arr[index].key == key ){
            return true;
        }
    }
}

bool HashMap::Add(string &key) {
    Entry ent = Entry( key );
    int index = -1;                      // индекс равен -1, поскольку такой позиции нет в векторе элементов

    if ( Has( key, index ) ){
        return false;
    }

    cout << index << endl;

    if( elemInArr < limit ){
            arr[index] = ent;
    }
    else {
        RebuildHashMap();
    }
    elemInArr++;
}

void HashMap::RebuildHashMap() {
    vector<Entry> tmp = arr;
    elemInArr = 0;
    arrSize *= 2;
    limit = 0.75 * arrSize;
    cout << "limit = " << limit << endl;
    vector<Entry>( arrSize ).swap( arr );
    for( int i = 0; i < arrSize / 2; i++ ){
        if( tmp[i].status == filled ){
            this->Add( tmp[i].key );
        }
    }
}

bool HashMap::Delete(string &key) {
    return false;
}


int main() {
    HashMap h( 8 );
    for( int i = 1; i < 44; i++ ){
        string s = "sdf" + to_string(i);
        h.Add(s);
    }
    return 0;
}

