#include <iostream>
#include <list>

using namespace std;

/*
                            Задача 1_4

 “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
 Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
 затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.)
 Необходимо определить номер уцелевшего.
*/

int findSurvivor(const int persons_count, const int step);

int main()
{
    int persons_count = 0,
        step = 0;

    cin >> persons_count >> step;

    int survivor = findSurvivor(persons_count, step);

    cout << survivor;

    return 0;
}

int findSurvivor(const int persons_count, const int step)
{
    int *persons_number = new int(persons_count);

    for(int i = 0; i < persons_count; ++i)
        persons_number[i] = i;

    int marker = 0,
        alive_count = persons_count;

    while(true)
    {
        if(alive_count == 1)
        {
            int survivor_number = persons_number[0] + 1;
            delete persons_number;
            return survivor_number;
        }

        marker = (marker + step - 1) % alive_count;

        for(int i = marker; i < alive_count - 1; ++i)
            persons_number[i] = persons_number[i + 1];

        alive_count--;
    }
}