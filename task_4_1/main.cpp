#include <iostream>
#include <vector>

/*
                            Задача 4_1

 Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы.
 Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм.
 За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно,
 откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит
 нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.

 Определить за сколько подходов Вовочка съест все фрукты в корзине.
*/

template <typename T>

struct max_prior_queue
{
    max_prior_queue() {}

    void push(const T value)
    {
        data_.push_back(value);
        move_up(data_.size() - 1);
    }

    const T top()
    {
        if (data_.size() == 0)
            return T();

        T max_val = data_.at(0);
        data_.at(0) = data_.at(data_.size() - 1);
        data_.pop_back();

        if (data_.size() == 0)
            return max_val;

        moveDown(0);

        return max_val;
    }

    const T viewTop() const
    {
        if (data_.size() == 0)
            return T();
        else
            return data_.at(0);
    }

    bool isEmpty() const
    {
        return data_.size() == 0;
    }

private:
    std::vector<T> data_;

    void move_up(unsigned int pos)
    {
        if (pos == 0)
            return;

        unsigned int parent_pos = pos / 2;

        if (data_.at(parent_pos) > data_.at(pos))
            return;

        T temp = data_.at(pos);
        data_.at(pos) = data_.at(parent_pos);
        data_.at(parent_pos) = temp;

        move_up(parent_pos);
    }

    void moveDown(unsigned int pos)
    {
        unsigned int child_1 = 2 * pos,
                     child_2 = 2 * pos + 1;

        if(child_1 > (data_.size() - 1))
            return;

        if(child_2 > (data_.size() - 1))
        {
            if(data_.at(pos) > data_.at(child_1))
                return;

            T temp = data_.at(pos);
            data_.at(pos) = data_.at(child_1);
            data_.at(child_1) = temp;

            return;
        }
        else
        {
            if (data_.at(pos) >= data_.at(child_1) && data_.at(pos) >= data_.at(child_2))
                return;
            else
            {
                unsigned int pos_to_swap = data_.at(child_1) > data_.at(child_2) ? child_1 : child_2;

                T temp = data_.at(pos);
                data_.at(pos) = data_.at(pos_to_swap);
                data_.at(pos_to_swap) = temp;

                moveDown(pos_to_swap);
            }
        }
    }
};


int main()
{
    int fructs_count = 0;
    std::cin >> fructs_count;

    max_prior_queue<int> queue;

    while (fructs_count > 0)
    {
        int value = 0;
        std::cin >> value;

        queue.push(value);
        --fructs_count;
    }

    int max_weight = 0;
    std::cin >> max_weight;

    std::vector<int>fructs;

    int steps_count = 0;

    while (!queue.isEmpty())
    {
        int current_weight = 0;

        int fruct = queue.top();
        fructs.push_back(fruct);
        current_weight += fruct;

        while (!queue.isEmpty())
        {
            int next_fruct = queue.viewTop();
            if (current_weight + next_fruct > max_weight)
                break;
            else
            {
                fructs.push_back(queue.top());
                current_weight += next_fruct;
            }
        }
        ++steps_count;

        for (auto fr : fructs)
            if (fr > 1) queue.push(fr / 2);

        fructs.clear();
    }
    
    std::cout << steps_count << std::endl;
    return 0;
}