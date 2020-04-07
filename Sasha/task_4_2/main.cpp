#include <iostream>
#include <assert.h>
#include <stdio.h>

/*
                            Задача 4_2

 Для сложения чисел используется старый компьютер. Время, затрачиваемое
 на нахождение суммы двух чисел равно их сумме. Таким образом для нахождения
 суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка
 вычислений.
 ((1+2)+3) -> 1+2 + 3+3 = 9
 ((1+3)+2) -> 1+3 + 4+2 = 10
 ((2+3)+1) -> 2+3 + 5+1 = 11
 Требуется написать программу, которая определяет минимальное время, достаточное
 для вычисления суммы заданного набора чисел.
 Требуемое время работы O(n*log(n)).
*/

// Куча целых чисел, реализованная с помощью массива
class class_Array
{
private:
    int *array;	                // Массив данных
    int size_array;	            // Размер кучи
    int elements_count;	        // Количество уже заполненных элементов
    void swap(int, int);		// Смена мест элементов с заданными индексами

public:
    class_Array(int size);
    ~class_Array() { delete array; };

    int count() { return elements_count; }; // Получение количества элементов

    int getFirst();             // Получение первого элемента
    void moveUp(int);           // Проталкивание элемента наверх
    void moveDown(int);         // Проталкивание элемента вниз
    void addElement(int);		// Добавление элемента
};

int class_Array::getFirst()
{
    int tmp = array[0];
    swap(0, --elements_count);
    moveDown(0);
    return tmp;
}

void class_Array::moveDown(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем меньшего сына, если такой есть.
    int largest = i;

    if(left < elements_count && array[left] < array[i])
        largest = left;

    if(right < elements_count && array[right] < array[largest])
        largest = right;

    // Если меньший сын есть, то проталкиваем корень в него.
    if(largest != i)
    {
        swap(i, largest);
        this->moveDown(largest);
    }
}

void class_Array::moveUp( int i )
{
    int parent;

    while(i > 0)
    {
        parent = (i - 1) / 2;

        if(array[i] <= array[parent])
            swap(i, parent);

        i = parent;
    }
}

void class_Array::swap(int i, int j)
{
    array[i] = array[i] ^ array[j];
    array[j] = array[i] ^ array[j];
    array[i] = array[i] ^ array[j];
}

class_Array::class_Array(int size): size_array(size), elements_count(0)
{
    array = new int[size_array]; // Создаем буфер.
}

void class_Array::addElement(int Data)
{
    array[elements_count] = Data;
    moveUp(elements_count);
    elements_count++;
}

//Расчет времени
int calculateTime(class_Array *Intarray)
{
    int time = 0;
    int Sum = 0;
    
    while (Intarray->count() > 1)
    {
        Sum = Intarray->getFirst();
        Sum += Intarray->getFirst();
        Intarray->addElement(Sum);
        time += Sum;
    }

    return time;
}

int main()
{
    //Получение количство слогаемых
    int elements_count = 0;

    if( scanf("%d\n", &elements_count) != 1)
        return 0;

    assert(elements_count >= 0);

    class_Array Intarray(elements_count);

    int num;

    for(int i = 0; i < elements_count; ++i)
    {
        scanf("%d", &num);
        Intarray.addElement(num);
    }

    printf("%d\n", calculateTime(&Intarray));

    return 0;
}