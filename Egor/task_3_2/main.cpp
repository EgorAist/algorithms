/*
                         Задача 3_2

 Реализовать дек с динамическим зацикленным буфером.

 Формат входных данных.
 В первой строке количество команд n. n ≤ 1000000.
 Каждая команда задаётся как 2 целых числа: a b.
     a = 1 - push front
     a = 2 - pop front
     a = 3 - push back
     a = 4 - pop back
 Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
 Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
 Если дана команда pop*, то число b - ожидаемое значение.
 Если команда pop вызвана для пустой структуры данных, то ожидается “-1”.
 Формат выходных данных.
 Требуется напечатать YES - если все ожидаемые значения совпали.
 Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.

 Требования: Дек должен быть реализован в виде класса.
*/

#include <iostream>
#include <cassert>

using namespace std;

#define MIN_SIZE 10
#define MEM_INCREASE 2

template <typename T>
// дек - это двусторонняя очередь
// элементы в дек можно класть и доставать
// как с начала, так и с конца
class Deque
{
public:
    Deque();  // конструктор
    ~Deque(); // деструктор

    void pushFront(const T &element); // положить спереди
    void pushBack(const T &element);  // положить сзади

    T popFront(); // достать элемент спереди
    T popBack();  // достать элемент сзади

    bool isEmpty(); // проверка на то, что дек пустой

private:
    // направление элементов в деке слева направо
    int tail; // хвостовой элемент (количество элементов - 1)
    int head; // головной элемент (0)

    T *buffer;       // буфер для хранения элементов
    size_t capacity; // вместимость буфера
    size_t size;     // количество элементов в деке
                     // (количество занятых элементов в буфере)
    
    void resize(); // изменить размер буфера
};

template <typename T>
Deque<T>::Deque(): head{0}, tail{0} 
{
    // выделение памяти под буфер
    buffer = new T[MIN_SIZE];
    // вместимость - количество элементов в буфере
    capacity = MIN_SIZE;
    // количество элементов в деке - 0
    size = 0;
}

template <typename T>
Deque<T>::~Deque() 
{
    // очистка памяти
    delete []buffer;
}

template <typename T>
bool Deque<T>::isEmpty() 
{
    // если size = 0, то вернуть 1
    return !size;
}


template <typename T>
void Deque<T>::pushBack(const T &element) 
{
    // проверка на то, что в буфере еще осталось место
    if (size + 1 > capacity)
        resize();

    // положить элемент в конец
    buffer[tail] = element;
    // увеличить количество реально занятого пространства в буфере
    size++;
    // так как дек зациклен, нужно искать остаток от деления
    tail = (tail + 1) % capacity;
}


template <typename T>
void Deque<T>::pushFront(const T &element)
{
    // проверка на то, что в буфере еще осталось место
    if (size + 1 > capacity)
        resize();

    // изменения положения головного элемента
    head = (head - 1 + capacity) % capacity;
    // кладем новый элемент в начало
    buffer[head] = element;
    // увеличить количество реально занятого пространства в буфере
    size++;
}


template <typename T>
T Deque<T>::popFront()
{
    // проверка дека на отсутствие элементов
    if (isEmpty())
        return -1;

    // возвращение головного элемента
    T return_element = buffer[head];
    // изменение положения головного элемента
    head = (head + 1) % capacity;
    // изменения размера дека
    size--;
    // возвращение нужного элемента
    return return_element;
}


template <typename T>
T Deque<T>::popBack()
{
    // проверка дека на отсутствие элементов
    if (isEmpty())
        return -1;

    // параресчет хвостового элемента
    tail = (tail - 1 + capacity) % capacity;
    // изменение размера дека
    size--;
    // возвращение нужного элемента
    return buffer[tail];
}


template <typename T>
void Deque<T>::resize() 
{
    // новое количество элементов в буфере -
    // это старое количество * 2
    size_t new_capacity = capacity * MEM_INCREASE;

    // выделяем память под новый буфер
    T *tmp = new T[new_capacity];

    // если головной элемент меньше, чем хвостовой
    if (head < tail) 
        copy(buffer + head, buffer + tail, tmp + head);
    else {
        /* Поскольку буфер зацикленный, tail может распологаться в начале массива,
         * соответственно он может быть меньше head. В этом случае расширяем зацикленный
         * буфер и поэтому копируем его частями */
        copy(buffer + head, buffer + capacity, tmp + head);
        copy(buffer, buffer + tail, tmp + capacity);
        tail = capacity + tail;
    }

    // изменяем количество элементов
    capacity = new_capacity;
    // очищаем буфер
    delete []buffer;
    // теперь буфер реалицированный
    buffer = tmp;
}

int main()
{
    // создаем объект класса дек
    Deque<int> deq;

    // количество элементов
    int n = 0;
    cin >> n;
    // проверка условий
    assert(n >= 0);

    bool flag = true;   // флаг для проверка корректности
    int cmd = 0;        // код команды
    int element = 0;    // элемент, с которым нужно выполнять действия
    int return_pop = 0; // возвращаемый элемент

    for (size_t i = 0; i < n; i++)
    {
        cin >> cmd >> element;

        switch (cmd)
        {
            // положить в начало
            case 1:
                deq.pushFront(element);
                break;

            // вернуть первый элемент
            case 2:
                return_pop = deq.popFront();
                // проверка на ошибку
                if (element != return_pop)
                    flag = false;
                break;

            // положить последний элемент
            case 3:
                deq.pushBack(element);
                break;

            // вернуть последний элемент
            case 4:
                return_pop = deq.popBack();
                // проверка на ошибку
                if (element != return_pop)
                    flag = false;
                break;

            default:
                break;
        }
    }

    if (flag)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
