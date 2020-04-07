#include <iostream>
#include <assert.h>

/*
                              Задача 1_3

   Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
   Найти количество таких пар индексов (i, j), что A[i] + B[j] = k.
   n, m ≤ 100000.
*/


using namespace std;

int findCountCoincidence(int size_arr_A, int *arr_A,
                         int size_arr_B, int *arr_B,
                         const int compare_element);

int main()
{
    // размер массива A
    int size_arr_A = 0;
    cin >> size_arr_A;

    // проверка размера массива A
    assert(size_arr_A > 0);

    // выделяем память под массива А
    int *arr_A = new int[size_arr_A];

    // заполняем массив А элементами
    for(int i = 0; i < size_arr_A; ++i)
        cin >> arr_A[i];

    // размер массива В
    int size_arr_B = 0;
    cin >> size_arr_B;

    // проверка размера массива В
    assert(size_arr_B > 0);

    // выделяем память под массив В
    int *arr_B = new int[size_arr_B];

    // заполняем массив В элементами
    for (int i = 0; i < size_arr_B; ++i)
        cin >> arr_B[i];

    // compare_element - k, элемент, который должен быть равен A[i] + B[j]
    int compare_element = 0;
    cin >> compare_element;

    // находим количество совпадений A[i] + B[j] равное k
    int count_coincidence = findCountCoincidence(size_arr_A, arr_A,
                                                 size_arr_B, arr_B,
                                                 compare_element);

    cout << count_coincidence;

    // чистим память
    delete []arr_A;
    delete []arr_B;

    return 0;
}



int findCountCoincidence(int size_arr_A, int *arr_A,
                         int size_arr_B, int *arr_B,
                         const int compare_element)
{
    int count_coincidence = 0, // количество совпадений A[i] + B[j]
        j = 0,
        i = 0;      // итераторы

    // если размер массива A <= В
    if (size_arr_A <= size_arr_B)
    {
        for (i = size_arr_B - 1; i >= 0;)
        {
            /* если A[j] + B[i] < k, то переходим
               к следующему элементу из массива А */
            if (arr_B[i] + arr_A[j] < compare_element)
                j++;

            /* если A[j] + B[i] = k, то количество совпадений +1,
               переходим к предыдущему элементу в массиве В */
            if (arr_B[i] + arr_A[j] == compare_element)
            {
                i--;
                count_coincidence++;
            }

            /* если А[j] + В[i] > k, то переходим
               к предыдущему элементу в массиве В */
            if (arr_B[i] + arr_A[j] > compare_element)
                i--;
        }
    }
    // если размер массива A > В
    else
    {
        for (i = size_arr_A - 1; i > 0;)
        {
            if (arr_A[i] + arr_B[j] < compare_element)
                j++;

            if (arr_A[i] == (compare_element - arr_B[j]))
            {
                count_coincidence++;
                i--;
            }

            if (arr_A[i] > (compare_element - arr_B[j]))
                i--;
        }
    }
    return count_coincidence;
}