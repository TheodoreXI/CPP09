#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
    *this = obj;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj)
{
    this->data = obj.data;
    return (*this);
}

void BitcoinExchange::fill(std::string &s)
{
    std::string buffer;
    std::fstream in_file(s.c_str());
    std::stringstream res;
    std::string out;
    std::string temp;
    int c = 0;
    double f;

    if (!in_file.is_open())
    {
        throw (std::runtime_error("Could not open file.\n"));
    }
    getline(in_file, buffer);
    while (getline(in_file, buffer))
    {
        res.clear();
        res.str(buffer);
        c = 0;
        while (getline(res, temp, ','))
        {
            if (!c)
                out = temp;
            c++;
        }
        res.clear();
        res.str(temp);
        res >> f;
        data[out] = f;
    }
}

void    remove_whitespace(std::string &s)
{
    if (s.empty())
        return ;
    size_t l = s.size();
    size_t st = 0;
    size_t en = l-1;
    while (st < en && std::isspace(s[st]))
        st++;
    while (en > st && std::isspace(s[en]))
        en--;
    s.erase(en+1);
    s.erase(0, st);
}

double BitcoinExchange::find_key(std::string &date)
{
    std::map<std::string, double>::iterator it = data.lower_bound(date);
    if (it == data.end())
    {
        std::cerr << "not date equal or less than the current date found.\n";
        return (0);
    }
    if (date != it->first)
    {
        if (it == data.begin())
        {
            return (it->second);
        }
        it--;
    }
    return (it->second);
}

void BitcoinExchange::process(const char *av)
{
	std::string buffer;
	std::string date;
	std::string value;
    std::fstream in_file(av);
	std::stringstream res;
    double d;
    if (!in_file.is_open())
    {
        throw (std::runtime_error("Error: Could not open file.\n"));
    }
	getline(in_file, buffer);
	if (buffer != "date | value")
	{
		throw (std::runtime_error("First line of file is incorrect, it should be <date | value>.\n"));
	}
	while (getline(in_file, buffer))
    {
        res.clear();
		res.str(buffer);
		getline(res, date, '|');
		getline(res, value);
        remove_whitespace(date);
        remove_whitespace(value);
        if (parse(date, value))
            continue;
        d = find_key(date);
        std::cout << date << " => " << value << " = " << (v*d) << "\n";
    }
}

int BitcoinExchange::parse(std::string &date, std::string &value)
{
    std::stringstream res(value);
    int count = 0;
    int v = 0;
    int white_count = 0;
	if (date.size() != 10)
	{
		std::cerr << "Error: bad input => " << date << "\n";
        return (1);
	}
    if (value.find('-') != std::string::npos)
    {
        std::cerr << "Error: not a positive number." << "\n";
        return (1);
    }
	for (size_t i = 0; i < date.size(); i++)
	{
        if (date[i] == '-')
            white_count++;
        if (white_count > 2)
        {
            std::cerr << "Error: bad input => " << date <<"\n";
            return (1);
        }
        if ((i <= 3 || (i > 4 && i < 7) || i > 7) && !std::isdigit(date[i]))
        {
			std::cerr << "Error: bad input => " << date <<"\n";
            return (1);
        }
		if ((i == 4 or i == 7) && date[i] != '-')
		{
			std::cerr << "Error: bad input => " << date <<"\n";
            return (1);
		}
	}
    if (value.empty())
    {
        std::cerr << "Error: empty value => " << value <<"\n";
        return (1);
    }
    for (size_t i = 0; i < value.size(); i++)
	{
        if (i && !count && value[i] == '.')
        {
            count++;
            continue;
        }
        if (count >= 2 || (value[i] == '.' && !i))
        {
            std::cerr << "Error: value => " << value <<"\n";
            return (1);
        }
        if (!std::isdigit(value[i]))
        {
            std::cerr << "Error: value => " << value <<"\n";
            return (1);
        }

    }
    res >> v;
    if (v > 1000)
    {
        std::cerr << "Error: too large a number.\n";
        return (1);
    }
    return (0);
}

