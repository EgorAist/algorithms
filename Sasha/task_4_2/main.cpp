#include <iostream>
#include <assert.h>
#include <stdio.h>

using namespace std;

/* Дергачев Александр

  Группа АПО-13

 Условие задачи 4_2
  
 Для сложения чисел используется старый компьютер. Время, затрачиваемое
 на нахождение суммы двух чисел равно их сумме. Таким образом для нахождения
 суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка
 вычислений.
*/

class class_Array
{
private:
    int *array;	                // Массив данных
    int size_array;	            // Размер кучи
    int elements_count;	        // Количество уже заполненных элементов
  
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
  //извлекаем первый элемент, при этом помещаем на его место последний элемент в куче, а также балансируем кучу
    int tmp = array[0];
    swap(array[0], array[elements_count]);
    moveDown(0);
    return tmp;
}

//балансируем кучу путем спуска элемента вниз 
void class_Array::moveDown(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    // Ищем меньшего сына
    int largest = i;

    if(left < elements_count && array[left] < array[i])
        largest = left;

    if(right < elements_count && array[right] < array[largest])
        largest = right;

    // Если меньший сын есть, то проталкиваем его в корень кучи 
    if(largest != i)
    {
        swap(array[i], array[largest]);
        this->moveDown(largest);
    }
}



//балансируем кучу путем поднятия элемента 
void class_Array::moveUp( int i )
{
    int parent;

    while(i > 0)
    {
        parent = (i - 1) / 2;

        if(array[i] <= array[parent])
            swap(array[i], array[parent]);

        i = parent;
    }
}

class_Array::class_Array(int size): size_array(size), elements_count(0)
{
    array = new int[size_array]; // Создаем буфер.
}

void class_Array::addElement(int Data)
{
    array[elements_count] = Data; //добавляем новый элемент
    moveUp(elements_count);       //балансируем кучу
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
    //Получение количества слагаемых
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
