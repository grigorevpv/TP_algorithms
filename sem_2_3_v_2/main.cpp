//
//                              Задача 3_1: "Реклама"
//      В этой задаче необходимо использовать локальную пирамидальную сортировку
// (без использования доп. памяти). Общее время работы алгоритма О(n*log[n]).
//
//      В спермаркете решили оптимизировать показ рекламы. Известно расписание
// прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо
// показать минимум 2 рекламы. Рекламу можно транслировать только в целочисленные
// моменты времени. Покупатель может видеть рекламу от момента прихода до момента
// ухода из магазина. В каждый момент времени показывается только одна реклама.
// Считается, что реклама показывается мгновенно. Если реклама показывается в
// момент ухода или прихода, то считается, что посетитель успел ее посмотреть.
// Требуется определить минимальное число показов рекламы.
//


#include <iostream>
#include <vector>
#include <cassert>

// Структура "Покупатель"
struct Customer {

    Customer(int enter = 0, int exit = 0);
    void print();

    int enter_time;
    int exit_time;
};

// Компараторы
template <typename T>
bool StdCompare(const T& a, const T& b) { return a < b; }
bool CustomerCompare(const Customer& a, const Customer& b) {

    return (a.exit_time == b.exit_time ?
            a.enter_time > b.enter_time :
            a.exit_time < b.exit_time); // a < b
}

// Пирамидальная сортировка
template <typename T>
void SiftDown(T* array, int parent, int end,
              bool (*Compare)(const T&, const T&)) {

    int left_son = 0,
        right_son = 0,
        largest = 0;

    while(true) { // O(log[end - parent])

        left_son = 2 * parent + 1;
        right_son = 2 * parent + 2;
        largest = parent;

        if (left_son < end && Compare(array[largest], array[left_son]))
            largest = left_son;
        if (right_son < end && Compare(array[largest], array[right_son]))
            largest = right_son;
        if (largest == parent)
            break;

        std::swap(array[parent], array[largest]);
        parent = largest;
    }
}
template <typename T>
void heapSort(T* array, int begin, int end,
              bool (*Compare)(const T&, const T&) = StdCompare) {

    assert(0 <= begin);
    assert(begin <= end);

    for (int i = (end - 1) / 2; i >= begin; --i) // O(n)
        SiftDown(array, i, end, Compare);

    for (int i = end - 1; i >= begin; --i) { // O(nlog[n])
        std::swap(array[i], array[begin]);
        SiftDown(array, begin, i, Compare);
    }

    // Итого: O(n) + O(nlog[n]) ~ O(nlog[n])
}

// Логика программы
int getAdvertise(std::vector<Customer> vector) {

    if (vector.size() == 0)
        return 0;
    int second = vector[0].exit_time;
    int first = second - 1;

    int count = 2;

    for (int i = 0; i < (int)vector.size(); ++i) {

        if (vector[i].enter_time <= first && second <= vector[i].exit_time)
            continue;

        if (second < vector[i].enter_time) {
            count += 2;
            second = vector[i].exit_time;
            first = second - 1;
            continue;
        }
        if (first < vector[i].enter_time && vector[i].enter_time <= second && second < vector[i].exit_time) {
            ++count;
            first = second;
            second = vector[i].exit_time;
        }
    }
    return count;
}

int main() {

    int size = 0;
    std::cin >> size;
    std::vector<Customer> array((unsigned)size);

    for (int i = 0; i < size; ++i) {

        std::cin >> array[i].enter_time;
        std::cin >> array[i].exit_time;
    }

    heapSort(&array[0], 0, (int)array.size(), CustomerCompare);

/*    for( auto i : array ){
        std::cout << i.enter_time << " " << i.exit_time << std::endl;
    }*/

    std::cout << getAdvertise(array);

    return 0;
}

// Реализация структуры
Customer::Customer(int enter, int exit) {

    enter_time = enter;
    exit_time = exit;
}
