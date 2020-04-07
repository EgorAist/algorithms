#include <iostream>

using namespace std;

/*
                                    Задача 2_4

 Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
 Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k],
 ближайшего по значению к B[i].
 n ≤ 110000, m ≤ 1000.
 Время работы поиска для каждого элемента B[i]: O(log(k)).
*/

int findTwinInRange(const int *array, int twink, int size_array);

int binarySearch(const int *array, int start, int end, int twink);

int main()
{
    int size_arr_A = 0,
        size_arr_B = 0;

    cin >> size_arr_A;

    int *arr_A = new int[size_arr_A];

    for (int i = 0; i < size_arr_A; i++)
        std::cin >> arr_A[i];

    std::cin >> size_arr_B;

    int *arr_B = new int[size_arr_B];

    for (int i = 0; i < size_arr_B; i++)
    {
        std::cin >> arr_B[i];
        std::cout << findTwinInRange(arr_A, arr_B[i], size_arr_B) << " ";
    }

    delete []arr_A;
    delete []arr_B;

    return 0;
}

int findTwinInRange(const int *array, int twink, int size_array)
{
    int start = 0;
    int end = 0;

    //special cases
    if (twink < array[0])
        return 0;

    if (twink > array[size_array - 1])
        return size_array - 1;

    //Here we find the range, which consists of twink
    while (array[end] < twink)
    {
        start = end + 1;
        if (end * 2 < size_array)
            //if(!end)
                end = 1;
            else
                end = end * 2;
        else
            end = size_array - 1;
    }

    //As we have ordered array, we should search the index of the nearest twink by binary search
    int nearest_index = binarySearch(array, start, end, twink);

    //Detect the nearest twink
    if (abs(array[nearest_index] - twink) < abs(array[nearest_index - 1] - twink))
        return nearest_index;
    else
        return nearest_index - 1;
}

int binarySearch(const int *array, int start, int end, int twink)
{
    int middle = 0;

    while (start != end)
    {
        middle = (end + start) / 2;
        if (twink <= array[middle])
            end = middle;
        else
            start = middle + 1;
    }

    return start;
}