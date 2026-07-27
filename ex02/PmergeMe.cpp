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

