#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void)
{
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe &obj)
{
    *this = obj;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
    if (this != &obj)
    {
        this->vect_cont = obj.vect_cont;
        this->list_cont = obj.list_cont;
    }
    return (*this);
}


PmergeMe(const char **av, size_t size)
{
    std::stringstream ss;
    std::stringstream convert;
    std::string word;
    int num = 0;
    for (size_t i = 1; i < size; i++)
    {
        ss.str(av[i]);
        while (ss >> word)
        {
            if (parsing(word))
                throw (std::runtime_error("bad input\n"));
            convert.str(word);
            convert >> num;
            if ((num == 2147483647 && word != "2147483647")
                || (num == -2147483648 && word != "-2147483648"))
            {
                throw (std::runtime_error("bad input\n"));
            }
            vect_cont.push_back(num);
            list_cont.push_back(num);
        }
    }
}
int parsing(std::string &word)
{
    for (size_t i = 0; i < word.size(); i++)
    {
        if (!std::isdigit(word[i]))
            return (1);
    }
    return (0);
}

std::vector<size_t> ft_jacob_seque(size_t m)
{
    std::vector<size_t> ja;
    ja.push_back(1);
    ja.push_back(1);
    int i = 1;
    while (ja[i] < m)
    {
        i++;
        ja.push_back(ja[i-1]+2*ja[i-2]);
    }
    return (ja);
}


std::vector<size_t> PmergeMe::generate_jacob(size_t m)
{
    std::vector<size_t> js;
    js.push_back(1);
    js.push_back(1);
    size_t i = 1;
    while (js[i] < m)
    {
        i++;
        js.push_back(js[i-1]+2*js[i-2]);
    }
    return (js);
}

std::vector<size_t> PmergeMe::insert_order(size_t m)
{
    std::vector<size_t> o;
    if (m < 2)
        return (o); // needs explain
    std::vector<size_t> js = generate_jacob(m);
    size_t prev = 1;
    size_t l = 0;
    for (size_t i = 2; i < js.size(); i++)
    {
        l = std::min(js[i], m);
        for (size_t j = l; j > prev; j--)
            o.push_back(j);
        prev = l;
    }
    return (o);
}

void binaryInsert(std::vector<int> &m, std::vector<int>::iterator b, int v)
{
    std::vector<int>::iterator it = std::lower_bound(m.begin(), b, v);
    m.insert(it, v);
}

std::vector<int> PmergeMe::sorted(std::vector<int> &vect_cont)
{
    if (vect_cont.size() <= 1)
        return (vect_cont);
    std::vector<std::pair<int, int> > ps;
    int left = 0;
    if (vect_cont.size() % 2)
        left = 1;
    int f = 0;
    int s = 0;
    int t = 0;
    for (size_t i = 0; (i+1) < vect_cont.size(); i += 2)
    {
        f = vect_cont[i];
        s = vect_cont[i+1];
        if (f < s)
        {
            t = f;
            f = s;
            s = t;
        }
        ps.push_back(std::make_pair(f,s));
    }
    if (left)
        left = vect_cont[vect_cont.size()-1];
    std::vector<int> w;
    for (size_t i = 0; i < ps.size(); i++)
    {
        w.push_back(ps[i].first);
    }
    w = sorted(w);
    std::vector<int> m;
    std::vector<int> p;
    m.push_back(w[0]);
    //pushing back the first winner
    for (size_t i = 0; i < ps.size(); i++)
    {
        if (ps[i].first == w[0])
        {
            m.insert(m.begin(), ps[i].second);
            break;
        }
    }
    //inserting the first loser
    for (size_t i = 1; i < w.size(); i++)
        m.push_back(w[i]);
    //pushing back the rest of the winners

    for (size_t i = 1; i < w.size(); i++)
    {
        for (size_t j = 0; j < ps.size(); j++)
        {
            if (ps[j].first == w[i])
            {
                p.push_back(ps[j].second);
                break;
            }
        }
    }
    std::vector<size_t> loser_order = insert_order(w.size());
    size_t w_i = 0;
    size_t p_i = 0;
    int v = 0;
    int w_v = 0;
    std::vector<int>::iterator b;
    for (size_t i = 0; i < loser_order.size(); i++)
    {
        w_i = loser_order[i];
        p_i = w_i - 2;
        v = p[p_i];
        w_v = w[w_i-1];
        b = std::find(m.begin(), m.end(), w_v);
        binaryInsert(m, m.end(), v);
    }
    if (left)
        binaryInsert(m, m.end(), left);
    return (m);
}

void binaryInsertList(std::list<int> &m, std::list<int>::iterator b, int v)
{
    std::list<int>::iterator it = std::lower_bound(m.begin(), b, v);
    m.insert(it, v);
}

std::list<int> PmergeMe::sortedli(std::list<int> &list_cont)
{
    if (list_cont.size() <= 1)
        return (list_cont);
    std::vector<std::pair<int, int>> ps;
    int left = 0;
    if (list_cont.size() % 2)
        left = 1;
    int t = 0;
    int f = 0;
    int s = 0;
    std::list<int>::iterator itf;
    std::list<int>::iterator its;
    std::list<int>::iterator it = list_cont.begin();
    while (it != list_cont.end())
    {
        itf = it;
        it++;
        if (it == lit_cont.end())
        {
            left = 1;
            left = *itf;
            break;
        }
        its = it;
        it++;
        f = *itf;
        s = *its;
        if (f < s)
        {
            t = f;
            f = s;
            s = t;
        }
        ps.push_back(std::make_pair(f, s));
    }
    std::list<int> w;
    for (size_t i = 0; i < ps.size(); i++)
        w.push_back(ps[i].first);
    //popilating the winners
    w = sorted(w);
    std::list<int> m;
    std::vector<int> p;
    m.push_back(w.front());
    for (size_t j = 0; j < ps.size(); j++)
    {
        if (ps[j].first == w.front())
        {
            m.push_front(ps[j].second);
            break;
        }
    }
    std::list<int>::iterator wit = w.begin();
    wit++;
    while (wit != w.end())
    {
        m.push_back(*wit);
        wit++;
    }
    wit = w.begin();
    wit++;
    int v = 0;
    while (wit != w.end())
    {
        v = *wit;
        for (size_t i = 0; i< ps.size(); i++)
        {
            if (ps[j].first == v)
            {
                p.push_back(ps[j].second);
                break;
            }
        }
        wit++;
    }
    //inserting losers by order of the winners to the pend
    std::vector<size_t> loser_order = insert_order(w.size());
    size_t w_i = 0;
    size_t p_i = 0;
    v = 0;
    int w_v = 0;
    std::list<int>::iterator b;
    for (size_t i = 0; i < loser_order.size(); i++)
    {
        w_i = loser_order[i];
        p_i = w_i-2;
        v = p[p_i];
        wit = w.begin();
        std::advance(wit, w_i-1);
        w_v = *wit;
        b = std::find(m.begin(), m.end(), w_v);
        binaryInsertList(m, bound, v);
    }
    if (left)
        binaryInsertList(m, m.end(), left);
    return (m);
}

void PmergeMe::final_sort_vect(std::vector<int> &vect_cont)
{
    vect_cont = sorted(vect_cont);
}

void PmergeMe::final_sort_list(std::list<int> &list_cont)
{
    list_cont = sortedli(list_cont);
}

std::vector<int> &PmergeMe::get_vect(void)
{
    return (vect_cont);
}

std::list<int> &PmergeMe::get_list(void)
{
    return (list_cont);
}