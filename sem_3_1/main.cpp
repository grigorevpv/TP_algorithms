/*
 Реализуйте структуру данных типа “множество строк” на основе динамической
хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество,
удаления строки из множества и проверки принадлежности данной строки множеству.
 1_2.​ Для разрешения коллизий используйте двойное хеширование.
 */

#include <iostream>
#include <vector>
#include <cassert>

#define HASH_P1 19
#define HASH_P2 17

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
    int Hash( const string& key ) const;
    int Hash2( const string &key ) const;
    void RebuildHashMap();
};

// хеш1
int HashMap::Hash(const string &key) const {
    int hash = 0;
    for(int i = key.size() - 1; i >= 0; i--) {
        hash += (HASH_P1 * hash + key[i]) % arrSize;
    }
    return hash % arrSize;
}

// хеш2
int HashMap::Hash2( const string &key ) const {
    int hash = 0;
    for(int i = key.size() - 1; i >= 0; i--) {
        hash += (HASH_P2 * hash + key[i]) % arrSize;
    }
    return (2 * hash + 1) % arrSize;
}

// конструктор хеш-таблицы
HashMap::HashMap( int size ) {
    arr.resize(size);
    elemInArr = 0;
    arrSize = size;
    limit = arrSize * 0.75;        // 3/4 от размера массива
}

// проверкаа на принадлежность хеш-таблице
bool HashMap::Has( const string &key, int& position ) const {
    int h1 = Hash( key ),
            h2 = Hash2( key );

    for (int i = 0; i < arrSize; i++) {

<<<<<<< HEAD
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
=======
        if ( arr[h1].key == key && arr[h1].status != deleted ) {
            position = h1;
            return true;
        }

        if (arr[h1].status == empty && position < 0) {
            position = h1;                            // назначаем позицию только в том случае, если до этого не встречалась ячейка с удаленным элементом
            return false;
        }

        if ( arr[h1].status == deleted && position < 0 ) {
            position = h1;
>>>>>>> f49983acbb96225b620be9475fe99fc36a2f2fee
        }

        h1 = (h1 + h2) % arrSize;
    }
    return false;
}

// добавление в хеш-таблицу
bool HashMap::Add(string &key) {
    Entry ent = Entry( key );
    int index = -1;                      // индекс равен -1, поскольку такой позиции нет в векторе элементов

    if ( Has( key, index ) )
        return false;

        arr[index] = ent;
        elemInArr++;

    if( elemInArr >= limit )
        RebuildHashMap();

    return true;
}

// перехеширование при превышении размера
void HashMap::RebuildHashMap() {
    vector<Entry> tmp = arr;
    elemInArr = 0;
    arrSize *= 2;
    limit = 0.75 * arrSize;
    vector<Entry>( arrSize ).swap( arr );

    for( int i = 0; i < arrSize / 2; i++ ){

        if( tmp[i].status == filled ){
            this->Add( tmp[i].key );
        }
    }
}

// удаление элемента по ключу
bool HashMap::Delete(string &key) {
    int position = -1;

    if( Has( key, position ) ){
        elemInArr--;
        arr[position].status = deleted;
        arr[position].key = "";
        return true;
    }

    return false;
}


int main() {
<<<<<<< HEAD
    HashMap h( 8 );
//    string s = "sdf13";
//    h.Add(s);
    for( int i = 1; i < 44; i++ ){
        string s = "sdf" + to_string(i);
        cout << " s = " << s << endl;
        h.Add(s);
=======

    HashMap table( 8 );

    char command = 0;
    int position = -1;
    std::string value;

/*    value = "a";
    cout << value.size() - 1 << endl;*/

    while( std::cin >> command >> value ) {
        position = -1;
        bool commandSucceeded = false;
        switch( command ) {
            case '+':
                commandSucceeded = table.Add( value );
                break;
            case '-':
                commandSucceeded = table.Delete( value );
                break;
            case '?':
                commandSucceeded = table.Has( value, position );
                break;
            default:
                assert( false );
        }
        std::cout << ( commandSucceeded ? "OK" : "FAIL" ) << std::endl;
>>>>>>> f49983acbb96225b620be9475fe99fc36a2f2fee
    }
    return 0;
}

