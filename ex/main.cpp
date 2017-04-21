#include <iostream>
#include <vector>

using namespace std;

struct Entry{
    string val;
    int key;

    Entry() : val("0"), key(0) {};
    Entry( string& v, int k ) : val(v), key(k) {};
};

int main() {
    vector<int> arr;
    arr.resize(5);
    vector<Entry> arr2;
    arr2.resize(5);
    arr[0] = 5;
    arr[1] = 4;

    for( auto i : arr ){
        cout << i << " ";
    }
    cout << endl;
    vector<int>(15, 0).swap(arr);

    for( auto i : arr ){
        cout << i << " ";
    }

    cout << endl;

    int k = 10;
    string s = "sdfsdf" + to_string(k);

    cout << s;




    return 0;
}