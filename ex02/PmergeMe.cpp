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
    m.push_back(w[0]);
    // push the winner in main
    for (size_t i = 0; i < ps.size(); i++)
    {
        if (ps[i].first == w[0])
        {
            m.insert(m.begin(), p[i].second);
            break;
        }
    }
    //push the loser of the winner in main
    for (size_t i = 1; i < w.size(); i++)
        m.push_back(w[i]);
    //push every other winner
    for (size_t i = 1; i < w.size(); i++)
    {
        for (size_t j = 0; j < ps.size(); j++)
        {
            if (ps[j].first == w[k])
            {
                p.push_back(ps[j].second);
                break;
            }
        }
    }
    //insert pend with losers
    std::vector<size_t> loser_order =  insert_order(w.size());
    //the loser inserted order in the pend
    for (size_t i = 0; i < loser-order.size(); i++)
    {
        
    }
}

void PmergeMe::final_sort(std::vector<int> &vect_cont)
{
    vect_cont = sorted(vect_cont);
}