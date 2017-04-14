/*
3_1
В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода
покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.
Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может
видеть рекламу от момента прихода до момента ухода из магазина.
В каждый момент времени может показываться только одна реклама. Считается, что реклама
показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается,
что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.
 * */


#include <iostream>
#include <vector>

using namespace std;

// структура покупателей
struct Enter{
    int start;
    int finish;

    Enter() : start( 0 ), finish( 0 ) {};
    Enter( int s, int f ) : start( s ), finish( f ) {};
};

bool operator> ( const Enter& left, const Enter& right ){
    return left.finish == right.finish ?
           left.start > right.finish :
           left.finish < right.finish;
}

template <class T>
void siftDown( vector<T>& arr, int index, int bottom ){

    int left_son = 0,
            right_son = 0,
            largest = 0;

    while(true) { // O(log[end - parent])

        left_son = 2 * index + 1;
        right_son = 2 * index + 2;
        largest = index;

        if (left_son < arr.size() && arr[largest] > arr[left_son])
            largest = left_son;
        if (right_son < arr.size() && arr[largest] > arr[right_son])
            largest = right_son;
        if (largest == index)
            break;

        std::swap(arr[index], arr[largest]);
        index = largest;
    }


    /*int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if( left < bottom && arr[index] > arr[left] ){
        largest = left;
    }

    if( right < bottom && arr[largest] > arr[right] ){
        largest = right;
    }

    if( largest != index ) {
        swap(arr[index], arr[largest]);
        siftDown( arr, largest, bottom );
    }*/
}

template <class T>
void sortHeap( vector<T>& arr ){

    for (int i = (arr.size() - 1) / 2; i >= 0; --i) // O(n)
        siftDown( arr, i, arr.size() );

    for (int i = arr.size() - 1; i >= 0; --i) { // O(nlog[n])
        std::swap(arr[i], arr[0]);
        siftDown( arr, 0, i );
    }

}

int countAdvertising(std::vector<Enter>& arr) {

    if (arr.size() == 0)
        return 0;
    int second = arr[0].finish;
    int first = second - 1;

    int count = 2;

    for (int i = 0; i < (int)arr.size(); ++i) {

        if (arr[i].start <= first && second <= arr[i].finish)
            continue;

        if (second < arr[i].start) {
            count += 2;
            second = arr[i].finish;
            first = second - 1;
            continue;
        }
        if (first < arr[i].start && arr[i].start <= second && second < arr[i].finish) {
            ++count;
            first = second;
            second = arr[i].finish;
        }
    }
    return count;
}

int main() {
    int count = 0;
    cin >> count;
    vector<Enter> arr( (unsigned)count );

    for( int i = 0; i < count; ++i ) {

        std::cin >> arr[i].start;
        std::cin >> arr[i].finish;
    }

    sortHeap( arr );

/*    for( auto i : arr ){
        cout << i.start << " " << i.finish << endl;
    }*/

    cout << countAdvertising( arr ) << endl;

    return 0;
}