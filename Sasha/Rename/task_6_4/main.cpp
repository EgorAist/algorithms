#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*
                                      Задача 6_4

 Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..10^9] размера n.
 Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции
 с индексом k ∈[0..n-1] в отсортированном массиве.
 Напишите нерекурсивный алгоритм.
 Требования к дополнительной памяти: O(n).
 Требуемое среднее время работы: O(n).
 Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
 Описание для случая прохода от начала массива к концу:
 Выбирается опорный элемент.
 Опорный элемент меняется с последним элементом массива.
 Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
 Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат
 нерассмотренные элементы. Последним элементом лежит опорный.
 Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
 Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
 Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного,
 то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
 В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

 Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 Функцию Partition реализуйте методом прохода двумя итераторами от
 конца массива к началу.
*/

int Partition(int *array, int left, int right)
{

    // Выбор произвольного элемента массива и обмен его с первым элементом
    if (left != right)
        swap(array[left + rand() % (right - left)], array[left]);

    int x = array[left];

    // два счетчика справа
    int i = right + 1;

    for (int j = right; j >= left; --j)
        if (array[j] >= x)
            swap(array[--i], array[j]);

    return i;
}

int KStat(int *array, const int k_index, int elements_count)
{
    srand(time(NULL));

    int left_index = 0,
    	right_index = elements_count;

    while(true)
    {
        int position = Partition(array, left_index, right_index);
        //проверяем больше или меньше индекс найденного элемента
        //если меньше, то делаем проход по правому отрезку
        if (position < k_index)
			left_index = position + 1;
        //если больше - по левому
        else if (position > k_index)
			right_index = position - 1;
        //возвращаем ответ
        else
            return array[k_index];
    }
}

int main()
{
    int elements_count = 0,
        index = 0;
    cin >> elements_count >> index;

    int *array = new int[elements_count];

    for (int i = 0; i < elements_count; i++)
    {
        int element;
        cin >> element;
        array[i] = element;
    }

    cout << KStat(array, index, elements_count - 1);

    delete [] array;

    return 0;
}