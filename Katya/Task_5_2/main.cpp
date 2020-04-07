/*Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
 * Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
 * Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
 * В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
 * Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
 *
 * input
 * 3
    2 5 1980 13 11 2055
    1 1 1982 1 1 2030
    2 1 1920 2 1 2000

    ouput
    3
*/

#include <iostream>
#include <cstdio>

#define EVENT_TYPE_BECAME_MATURE 0
#define EVENT_TYPE_DIED_OR_TOO_OLD 1

// "событийная" структура для фиксирования таких пограничных дат, как совершеннолетие и смерть/достижение 80-летия
struct Event {
    int type;
    int day;
    int month;
    int year;

    Event(int type, int day, int month, int year) {
        this->type = type;
        this->day = day;
        this->month = month;
        this->year = year;
    }
};

// эта странная херня сделана, как я поняла, чтstd::less<T>()(arr[i], arr[j])обы переопределить работу функции less из std при использовании ее с ()
// при использовании std::less<T>()(arr[i], arr[j]) (в функции сортировки) сравниваются не просто числа, а поля структуры (проверяется год, месяц, день и тип)
namespace std
    template<>
    struct less<Event *>
    {
        bool operator()(const Event *obj1, const Event *obj2) const
        {
            if (obj1->year < obj2->year) return true;
            else if (obj1->year == obj2->year && obj1->month < obj2->month) return true;
            else if (obj1->year == obj2->year && obj1->month == obj2->month && obj1->day < obj2->day) return true;
            else if (obj1->year == obj2->year && obj1->month == obj2->month && obj1->day == obj2->day && obj1->type > obj2->type) return true;
            else return false;
        }
    };
}

void print_event(Event *event) {
    std::cout << "type " << event->type << " day " << event->day << " month " << event->month << " year" << event->year << std::endl;
}

//функция для проверки, является ли указанный человек совершеннолетним
bool isMature(int born_day, int born_month, int born_year, int died_day, int died_month, int died_year) {
    return (died_year < born_year + 18)
           || (died_year == born_year + 18 && died_month < born_month)
           || (died_year == born_year + 18 && died_month == born_month && died_day < born_day);
}

//аналогично
bool isDied(int born_day, int born_month, int born_year, int died_day, int died_month, int died_year) {
    return (died_year < born_year + 80)
           || (died_year == born_year + 80 && died_month < born_month)
           || (died_year == born_year + 80 && died_month == born_month && died_day < born_day);
}


//функция для создания структур событий для введенных людей
Event **CreateEventsByPersons(size_t &n) {
    //Event **events = new Event*[n * 2];
    Event **events = new Event*[n * 2]; //увеличиваем вдвое, потому что для каждого человека 2 крайние точки

    for (size_t i = 0; i < n; ++i) {
        int born_day, born_month, born_year;
        int died_day, died_month, died_year;

        //считваем даты
        scanf("%u %u %u %u %u %u", &born_day, &born_month, &born_year, &died_day, &died_month, &died_year);

        //если человек умер несовершеннолетним (даже в день 18летия) - не учитываем его
        if (isMature(born_day, born_month, born_year, died_day, died_month, died_year)) {
            --i;
            --n;

            continue;
        }

        //создаем структуру для точки совершеннолетия
        Event *became_mature_event = new Event(EVENT_TYPE_BECAME_MATURE, born_day, born_month, born_year + 18);

        events[2 * i] = became_mature_event;
        //каждый четный элемент массива - дата совершеннолетия


        //каждый нечетный - либо дата смерти (если она до 80 лет), либо 80-летия
        if (isDied(born_day, born_month, born_year, died_day, died_month, died_year)) {
            Event *died_event = new Event(EVENT_TYPE_DIED_OR_TOO_OLD, died_day, died_month, died_year);

            events[2 * i + 1] = died_event;
        } else {
            Event *too_old_event = new Event(EVENT_TYPE_DIED_OR_TOO_OLD, born_day, born_month, born_year + 80);

            events[2 * i + 1] = too_old_event;
        }
    }

    return events;
}

template <typename T>
void merge(T *arr, int low, int high, int mid, size_t events_num)
{
    Event **buf = new Event*[events_num];
    int i, j, k;
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (std::less<T>()(arr[i], arr[j])) {
        //if (arr[i] < arr[j]) {
            buf[k] = arr[i];
            k++;
            i++;
        }
        else  {
            buf[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        buf[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        buf[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)  {
        arr[i] = buf[i];
    }
}

/*template <typename T>
void merge_sort(T *arr, int low, int high, size_t events_num)
{
    int mid;
    if (low < high){
        //divide the array at mid and sort independently using merge sort
        mid=(low+high)/2;
        merge_sort(arr, low, mid, events_num);
        merge_sort(arr, mid+1, high, events_num);
        //merge or conquer sorted arrays
        merge(arr, low, high, mid, events_num);
    }
}*/
/*
void merge_sort(int *arr, int low, int high)
{
    int mid;
    if (low < high){
        //divide the array at mid and sort independently using merge sort
        mid=(low+high)/2;
        merge_sort(arr,low,mid);
        merge_sort(arr,mid+1,high);
        //merge or conquer sorted arrays
        merge(arr,low,high,mid);
    }
}
*/

// Merge sort


//функция сортировки полученных структур
template <typename T>
void quick_sort(T *a, size_t n) {
    size_t i = 0;
    size_t j = n - 1;
    bool side = 0;

    while (i != j) {
        if (!std::less<T>()(a[i], a[j])) {
            std::swap(a[i], a[j]);
            side = !side;
        }

        if (side) {
            ++i;
        } else {
            --j;
        }
    }

    if (i > 1) quick_sort(a, i);
    if (i + 1 < n) quick_sort(a + i + 1, n - (i + 1));
}

int FindMaxValid(Event **events, size_t events_num) {
    int valid = 0;
    int valid_max = 0;

    for (size_t i = 0; i < events_num; ++i) {
        if (events[i]->type == EVENT_TYPE_BECAME_MATURE) {
            ++valid;

            print_event(events[i]);
            std::cout << "valid = " << valid << std::endl;
        } else if (events[i]->type == EVENT_TYPE_DIED_OR_TOO_OLD) {
            --valid;

            print_event(events[i]);
            std::cout << "valid = " << valid << std::endl;
        }

        if (valid > valid_max) {

            valid_max = valid;

            std::cout << "valid max = " << valid_max << std::endl;
        }

        std::cout << std::endl;
    }

    return valid_max;
}

int main() {
    size_t n = 0;

    //считывание количества человек
   scanf("%u", (unsigned *)&n);
    //scanf("%u", &n);


    //создаются структуры для введенных людей
    Event **events = CreateEventsByPersons(n);
//    если что, это не двумерный массив, а одномерный массив указателей на структуры (поскольку они будут формироваться в другой функции)

    size_t events_num = n * 2;
    //поскольку для каждого человека создаются 2 пограничные сруктуры, увеличиваем n вдвое

    std::cout << "after create " << std::endl;
    for (int i = 0; i < events_num; i++)
        print_event(events[i]);
    std::cout << std::endl;


   // merge_sort<Event *>(events, 0, events_num - 1, events_num);

   //сортируем структуры, которые выглядят как дата и тип даты (дата совершеннолетия имеет тип 0, поэтому они будут в первой половине отсортированного массива)
    quick_sort<Event *>(events, events_num);
    std::cout << "after sort " << std::endl;
    for (int i = 0; i < events_num; i++)
        print_event(events[i]);
    std::cout << std::endl;


    //находим максимальное количество современников при помощи отсортированного массива
    // как математически это работает, я не понимаю, возможно это очень специфичная херня, которую надо знать
    int valid_max = FindMaxValid(events, events_num);

    printf("%u", valid_max);

    ///// еще раз - эта херня как-то работает, но quick sort нам не подходит, а если ты раскоментишь merge, оно не пройдет по времени
    ///// поэтому чтобы оно прошло, надо как-то переписывать логику

    return 0;
}
