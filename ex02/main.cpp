#include "PmergeMe.hpp"

double micro_sec(void)
{
    struct timeval t;
    gettimeofday(&t, 0);
    return (t.tv_sec * 1000000.0 + t.tv_usec);
}

template <typename T>
void print(T &a)
{
    typename T::iterator it = a.begin();
    while (it != a.end())
    {
        if (it != a.begin())
        {
            std::cout << ' ';
        }
        std::cout << *it;
        it++;
    }
    std::cout << std::endl;
}

int main(int ac, char **av)
{
    if (ac == 1)
    {
        std::cerr << "need more numbers\n";
        return (1);
    }
    try
    {
        PmergeMe p(av, static_cast<size_t>(ac));
        std::cout << "Before: ";
        print(p.get_vect());
        double start = micro_sec();
        p.final_sort_vect(p.get_vect());
        double end = micro_sec() - start;

        double lstart = micro_sec();
        p.final_sort_list(p.get_list());
        double lend = micro_sec() - lstart;

        std::cout << "After: ";
        print(p.get_vect());
        std::cout.setf(std::ios::fixed);
        std::cout.precision(5);
        std::cout << "Time to process a range of " << p.get_vect().size() << " elements with std::vector : " << end << " us\n";
        std::cout <<  "Time to process a range of " << p.get_list().size() << " elements with std::list : " << lend << " us\n";
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << "\n";
        return (1);
    }
    return (0);
}