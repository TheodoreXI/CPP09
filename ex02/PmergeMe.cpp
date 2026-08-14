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

PmergeMe &operator=(const PmergeMe &obj)
{
    if (this != &obj)
    {
        this->raw_cont = obj.raw_cont;
    }
    return (*this);
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

PmergeMe(char **av, size_t size)
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

std::vector<int> PmergeMe::sorted(std::vector<int> &vect_cont)
{
    if (vect_cont.size() == 1)
        return (vect_cont);
    std::vector<std::pair<int, int>> ps;
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
}

void PmergeMe::final_sort(std::vector<int> &vect_cont)
{
    vect_cont = sorted(vect_cont);
}