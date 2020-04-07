#include <iostream>
using namespace std;

/*
                            Задача 4_3

 На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 Этот вокзал является их конечной станцией. Дано расписание движения электричек,
 в котором для каждой электрички указано время ее прибытия, а также время
 отправления в следующий рейс. Электрички в расписании упорядочены по времени прибытия.
 Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
 При этом если электричка из какого-то тупика отправилась в момент времени X, то электричку,
 которая прибывает в момент времени X, в этот тупик ставить нельзя, а электричку,
 прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное количество тупиков
 для работы по расписанию. Напишите программу, которая по данному расписанию определяет,
 какое минимальное количество тупиков требуется для работы вокзала.

*/

class class_Heap
{
private:

    void moveDown(int index);
    void moveUp(int index);

    void reallocate();

    int *buffer;
    int size;
    int capacity;

public:

    class_Heap(int cap = 10);
    ~class_Heap();

    int extractMin();
    void insert(int element);
    int peekAtNext() { return isEmpty() ? 0 : buffer[0]; }

    bool isEmpty() { return size == 0; }
    int getSize() { return size; }

};

// Подсчет минимально необходимого количества тупиков
int countDeadends(const int count);

int main()
{
    int n = 0;
    cin >> n;

    int min_count_deadends = countDeadends(n);
    cout << min_count_deadends;

    return 0;
}

class_Heap::class_Heap(int cap)
{
    capacity = cap;
    size = 0;
    buffer = new int[capacity];
}

class_Heap::~class_Heap()
{
    delete[] buffer;
}

void class_Heap::moveDown(int index)
{
    int left_son = 2 * index + 1;
    int right_son = 2 * index + 2;

    int smallest_son = index;

    if (left_son < size && buffer[left_son] < buffer[index])
        smallest_son = left_son;

    if (right_son < size && buffer[right_son] < buffer[smallest_son])
        smallest_son = right_son;

    if (smallest_son != index)
    {
        swap(buffer[index], buffer[smallest_son]);
        moveDown(smallest_son);
    }
}

void class_Heap::moveUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (buffer[index] >= buffer[parent])
            return;

        swap(buffer[index], buffer[parent]);

        index = parent;
    }
}

void class_Heap::reallocate()
{
    int new_capacity = capacity * 2;
    int *new_buffer = new int[new_capacity];

    for (int i = 0; i < capacity; ++i)
        new_buffer[i] = buffer[i];

    delete[] buffer;

    buffer = new_buffer;
    capacity = new_capacity;
}

void class_Heap::insert(int element)
{
    buffer[size] = element;
    moveUp(size++);

    if (size == capacity)
        reallocate();
}

int class_Heap::extractMin()
{
    if (isEmpty())
        return 0;

    int result = buffer[0];

    buffer[0] = buffer[size - 1];
    size--;
    moveDown(0);

    return result;
}

// Подсчет минимально необходимого количества тупиков
int countDeadends(const int n)
{
    int minimum_deadends = 0,
        arrival = 0,
        departure = 0;

    class_Heap class_Heap;

    for ( int i = 0; i < n; i++ )
    {
        // Ввод времени прибытия и отбытия
        std::cin >> arrival >> departure;

        if (!class_Heap.isEmpty())
        {
            // Если некоторые электрички к моменту прибытия уехали - извлекаем
            while (arrival > class_Heap.peekAtNext())
                class_Heap.extractMin();
        }

        // Добавляем время отправления прибывшей
        class_Heap.insert(departure);

        // Смотрим, сколько путей занято
        if (class_Heap.getSize() > minimum_deadends)
            minimum_deadends = class_Heap.getSize();
    }

    return minimum_deadends;
}

