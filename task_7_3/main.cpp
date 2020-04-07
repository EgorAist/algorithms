#include <iostream>
//using namespace std;

#define BITS 63

inline int bit (long long number, int i);
void binaryQuickSort(long long *, int, int, int );

int main()
{
    int count;
    std::cin >> count;
    
    long long *array = new long long[count];

    for (int i = 0; i < count; ++i)
        std::cin >> array[i];

    binaryQuickSort(array, 0, count - 1, BITS);

    for (int i = 0; i < count; ++i)
        std::cout << array[i] << " ";

    return 0;
}

//Проверка наличия единицы в раряде под номером i
inline int bit (long long number, int i)
{
    return (number >> i) & 1;
}

void binaryQuickSort(long long *array, int left, int right, int d)
{
    /* Работает пока left <= right, т.е. все элементы справа от array[i]
       имеют 1 в d-й позиции, а все элементы слева имеют 0 в d-й позиции,
       или пока не прошли по всем битам
    */
    if ( right <= left || d < 0)
        return;

    int i = left,
        j = right;

    // Ищем 0 бит и меняем это число с тем, которое имеет 1 в позиции d
    while ( i != j )
    {
        while (bit(array[i] , d) == 0 && (i < j))
            i++;

        while (bit(array[j] , d) == 1 && (j > i))
            j--;

        std::swap(array[i], array[j]);
    }

    // У среднего элемента в d-й позиции 0, то сдаигаем правую границу на 1.
    if (bit(array[right], d) == 0)
        j++;

    binaryQuickSort(array, left, j - 1, d - 1 );
    binaryQuickSort(array, j, right, d - 1 );
}