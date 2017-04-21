/*
6_2. LSD для long long.
Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 10^6.
Отсортировать массив методом поразрядной сортировки LSD по байтам.
 */


#include <iostream>
#include <stdio.h>
#include <string.h>

#define BYTE 256

using namespace std;

int digit( long long number, int n, int& iter ){
    int result = 0;
    //cout << "number = " << number;

    for( int i = 1; i <= n; i++ ){
        result = number % 256;
        number /= 256;
    }

    if( result == 0 )
        iter++;

    return result;
}


void CountingSort2( long long* a, int n, int count, bool& flag ) {
    int iterator = 0;
    int* c = new int[BYTE];
    for( int i = 0; i < BYTE; ++i )
        c[i] = 0;
    for( int i = 0; i < n; ++i )
        ++c[digit( a[i], count, iterator )];
    if( iterator == n ){
        flag = true;
        return;
    } else {
        iterator = 0;
    }
    int sum = 0;
    for( int i = 1; i < BYTE; ++i ) {
        c[i] += c[i - 1]; // Концы групп.
    }
    long long* b = new long long[n];
    for( int i = n -1; i >= 0; --i ) {// Проход с конца.
        b[--c[digit( a[i], count, iterator )]] = a[i];
    }

/*    cout << " i = " << count << endl;
    for( int i = 0; i < n; i++ ){
        cout << a[i] << " ";
        cout << endl;
    }*/

    delete[] c;
    memcpy( a, b, n * sizeof( long long) );
    delete [] b;
}

void LSDSort( long long* arr, int n ){
    bool flag = false;
    for( int i = 0; i < sizeof( long long ); ++i ){
        CountingSort2( arr, n, i + 1, flag );
        if( flag )
            break;
    }
}

int main() {

    long count = 0;
    cin >> count;
    long long* mass = new long long[count];

    for(int i = 0; i < count; i++){
        cin >> mass[i];
    }

    LSDSort(mass, count);

    for(int i = 0; i < count; i++){
        cout << mass[i] << " ";
    }

    return 0;
}