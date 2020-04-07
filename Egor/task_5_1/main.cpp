#include <iostream>
#include <cstring>

using namespace std;

/*
                                Задача 5_1
 
 В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода
 покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.
 Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть
 рекламу от момента прихода до момента ухода из магазина. В каждый момент времени может
 показываться только одна реклама. Считается, что реклама показывается мгновенно.
 Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть.
 Требуется определить минимальное число показов рекламы.
 
*/

template <typename T>
void merge(const T *first_array, int first_len,
           const T *second_array, int second_len,
           T *result, less<T> cmp);

template <typename T>
void mergeSort(T *arr, int n);

struct Client
{        
    int begin = 0;
    int end = 0;
    int first_ad_index = -1;
    int second_ad_index = -1;
};

int main() 
{
    int n;
    cin >> n;

    Client *clients = new Client[n];
    for (int i = 0; i < n; ++i)
        cin >> clients[i].begin >> clients[i].end;
    
    mergeSort<Client>(clients, n);

    Client *prev_client = clients;
    prev_client -> first_ad_index = prev_client -> end-1;
    prev_client -> second_ad_index = prev_client -> end;
    
    int count = 2;
    for(int i = 1; i < n; ++i)
    {
        if(clients[i].begin <= prev_client -> first_ad_index)
            clients[i].first_ad_index = prev_client -> first_ad_index;
        
        if(clients[i].begin <= prev_client -> second_ad_index)
            if(clients[i].first_ad_index != -1)
                clients[i].second_ad_index = prev_client -> second_ad_index;
            else
                clients[i].first_ad_index = prev_client -> second_ad_index;
            
        if(clients[i].first_ad_index == -1)
        {
            clients[i].first_ad_index = clients[i].end - 1;
            count++;
        }
        
        if(clients[i].second_ad_index == -1)
        {
            clients[i].second_ad_index = clients[i].end;
            count++;
        }
        
        prev_client = clients + i;
    }

    std::cout << count;
    
    delete []clients;
    
    return 0;
}

class clientComparator
{        
public:
    bool operator() (const Client &left, const Client &right)
    {
        if(left.end == right.end)
            return left.begin >= right.begin;
        
        return left.end <= right.end;
    }
};

template <typename T>
void mergeSort(T *array, int n)
{
    if (n <= 1)
        return;
    
    int first_len = n / 2;
    int second_len = n - first_len;

    mergeSort(array, first_len);
    mergeSort(array + first_len, second_len);

    T *merged_array = new T[n];
    
    merge(array, first_len, array + first_len, second_len, merged_array, clientComparator());
    memmove(array, merged_array, sizeof(T) * n);
    
    delete[] merged_array;
}

template<typename T, typename Comparator>
void merge(const T *first_array, int first_len,
           const T *second_array, int second_len,
           T *result, Comparator cmp) 
{
    int i = 0, 
        j = 0,
        k = 0;
    
    while (i < first_len || j < second_len) 
    {
        if(i == first_len)
            while (j < second_len)
                result[k++] = second_array[j++];
            
        else if(j == second_len)
            while (i < first_len)
                result[k++] = first_array[i++];
        
        else
            result[k++] = cmp(first_array[i], second_array[j]) ? first_array[i++] : second_array[j++];
    }
}