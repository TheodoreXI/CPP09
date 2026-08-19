#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <exception>
#include <list>
#include <utility>
#include <cstddef>
#include <sys/time.h>
#include <algorithm>

class PmergeMe
{
    private:
        std::vector<int> base;
        std::vector<int> vect_cont;
        std::list<int> list_cont;
    public:
        PmergeMe(void);
        ~PmergeMe(void);
        PmergeMe(const PmergeMe &obj);
        PmergeMe &operator=(const PmergeMe &obj);
        PmergeMe(char **av, size_t size);
        std::vector<int> sorted(std::vector<int> &vect_cont);
        std::list<int> sortedli(std::list<int> &list_cont);
        void final_sort_vect(std::vector<int> &vect_cont);
        void final_sort_list(std::list<int> &list_cont);
        std::vector<size_t> generate_jacob(size_t m);
        std::vector<size_t> insert_order(size_t m);
        std::vector<int> &get_vect(void);
        std::list<int> &get_list(void);
};

#endif