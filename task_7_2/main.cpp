#include <iostream>
using namespace std;

/*
                            Задача 7_2

 Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 106.
 Отсортировать массив методом поразрядной сортировки LSD по байтам.

 */


// получаем n-ый байт числа
int getByte(long long number, size_t n)
{
    return number >> (8 * n) & 255;
}

// сортировка подсчетом массива чисел по n-ому байту
void countingSort(long long *data, size_t size, const size_t n)
{
    size_t counters[256];

    for(size_t i = 0; i < 256; i++)
        counters[i] = 0;

    // считаем количество чисел с разными значениями байта (от 0 до 255)
    for(size_t i = 0; i < size; i++)
        counters[getByte(data[i], n)]++;

    // расчитываем первые индексы для вставки чисел
    for(size_t i = 1; i < 256; i++)
        counters[i] += counters[i - 1];


    // массив для результатов
    long long *tmp = new long long[size];

    // создаем отсортированный массив результатов
    for(size_t i = size - 1; ; i--)
    {
        tmp[--counters[getByte(data[i], n)]] = data[i];
        if(i == 0)
            break;
    }

    // переписываем отсортированный массив в исходный
    for(size_t i = 0; i < size; i++)
        data[i] = tmp[i];

    delete[] tmp;
}

// сортировка LSD
void LSDSort(long long *data, size_t size)
{
    size_t totalBytes = sizeof(long long);

    for(size_t byte = 0; byte < totalBytes; byte++)
        countingSort(data, size, byte);
}

int main()
{
    size_t n = 0;
    cin >> n;

    long long *data = new long long[n];
    for(size_t i = 0; i < n; i++)
        cin >> data[i];

    LSDSort(data, n);

    for(size_t i = 0; i < n; i++)
        cout << data[i] << " ";

    delete []data;

    return 0;
}