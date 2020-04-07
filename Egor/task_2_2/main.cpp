#include <iostream>
using namespace std;

/*
                                    Задача 2_2

 Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
 а на интервале [m, n-1] строго убывают. Найти m за O(log m).
 Требования:  Время работы O(log m). Внимание! В этой задаче сначала нужно определить диапазон для
 бинарного поиска размером порядка m, а потом уже в нем делать бинарный поиск.
*/


int findIndex(int size_array, int* array);

int binarySearch(int right, int left, int* array, char flag);

int main()
{
    int size_array = 0;
    cin >> size_array;

    int *array = new int[size_array];

    for(int i = 0; i < size_array; ++i)
        cin >> array[i];

    std::cout << findIndex(size_array, array);

    delete []array;
    return 0;
}

int findIndex(int size_array, int* array)
{
    int left = 1,
        right = 2,
        answer = 0;
    char flag = 0;


    while (left <= size_array && right <= size_array)
    {
        if ((answer = binarySearch(left, right , array, flag)) != -1)
            return answer;
        else
        {
            left *= 2;
            right *= 2;

            if (right > size_array)
            {
                right = size_array - 1;
                flag = 1;
            }
        }
    }
    return answer;
}

int binarySearch(int left, int right, int *array, char flag)
{
    int middle = 0;

    while (left <= right)
    {

        if((left - 1) == 0 && array[left - 1] > array[left])
            return (left - 1);

        if (flag == 1)
            if (array[right] > array[right - 1])
                return right;

        middle = (left + right) / 2;

        if (array[middle] > array[middle - 1] && array[middle] > array[middle + 1])
            return middle;
        else if (array[middle - 1] > array[middle] && array[middle] > array[middle + 1] )
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}
