#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <exception>
#include <list>
#include <utility>

class PmergeMe
{
    private:
        std::vector<int> vect_cont;
        std::list<int> list_cont;
    public:
        PmergeMe(void);
        ~PmergeMe(void);
        PmergeMe(const PmergeMe &obj);
        PmergeMe &operator=(const PmergeMe &obj);
        PmergeMe(char **av, size_t size);
        std::vector<int> sorted(std::vector<int> &vect_cont);
        void final_sort();
        std::vector<size_t> generate_jacob(size_t m);
        std::vector<size_t> insert_order(size_t m);
};

#endif