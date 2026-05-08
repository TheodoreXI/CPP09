#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
    std::cout << "Default constructor called.\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj)
{
    *this = obj;
}

BitcoinExchange::~BitcoinExchange(void)
{
    std::cout << "Destructor called.\n";
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &obj)
{
    this->data = obj.data;
}

void BitcoinExchange::fill(std::string &s)
{
    std::string buffer;
    std::fstream in_file(s.c_str());
    std::stringstream res;
    std::string out;
    std::string temp;
    int c = 0;
    float f;

    if (!in_file.is_open())
    {
        throw (std::runtime_error("Could not open file.\n"));
    }
    getline(in_file, buffer);
    while (getline(in_file, buffer))
    {
        res.str(buffer);
        while (getline(res, temp, ','))
        {
            if (!c)
            {
                out = temp;
            }
            c++;
        }
        res.str(temp);
        res >> f;
        data[out] = f;
    }
}

void BitcoinExchange::process()
{
    
}