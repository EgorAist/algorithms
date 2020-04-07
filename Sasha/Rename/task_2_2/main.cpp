#include <iostream>
using namespace std;

/*
                                    Задача 2_2

 Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают,
 а на интервале [m, n-1] строго убывают. Найти m за O(log m).
 Требования:  Время работы O(log m). Внимание! В этой задаче сначала нужно определить диапазон для
 бинарного поиска размером порядка m, а потом уже в нем делать бинарный поиск.
*/


int findIndex(int* array, int size_array);
int binarySearch(int* array, int left, int right, char flag);

int main()
{
    int elements_count = 0;
    cin >> elements_count;

    int *array = new int[elements_count];

    for(int i = 0; i < elements_count; i++)
        cin >> array[i];

    cout << findIndex(array, elements_count);

    delete [] array;
    return 0;
}

int findIndex(int* array, int size_array)
{
    int left = 1,
        right = 2,
        answer = 0;
    char flag = 0;


    while (left <= size_array && right <= size_array)
    {
        if ((answer = binarySearch(array, left, right, flag)) != -1)
            return answer;
        else
        {
            left *= 2;
            right *= 2;

            if (right > size_array) //проверка на выход за границы массива
            {
                right = size_array - 1;
                flag = 1;
            }
        }
    }
    return answer;
}

int binarySearch(int* array, int left, int right, char flag)
{
    int middle = 0;

    while (left <= right)
    {

        if((left - 1) == 0 && array[left - 1] > array[left]) //проверка на то что элемент m имеет индекс 0
            return (left - 1);

        if (flag == 1) //проверка на то что m = n
            if (array[right] > array[right - 1])
                return right;

        middle = (left + right) / 2;

        if (array[middle] > array[middle - 1] && array[middle] > array[middle + 1]) //проверка на искомый элемент
            return middle;
        else if (array[middle - 1] > array[middle] && array[middle] > array[middle + 1] ) //проверка на то что массив убывает на данном отрезке
            right = middle - 1;
        else
            left = middle + 1;
    }
    return -1;
}