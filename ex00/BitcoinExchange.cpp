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

void    remove_whitespace(std::string &date, std::string &value)
{
    int s = (date.length() > value.length()) ? date.length() : value.length();
    int c_date = 0;
    int c_value = 0; 
    for (int i = 0; i < s; i++)
    {
        if (!c_date && i < date.length() && std::isspace(date[i]))
        {
            date.erase(i, 1);
        }
        else
            c_date = 1;
        if (!c_value && i < value.length() && std::isspace(value[i]))
        {
            value.erase(i, 1);
        }
        else
            c_value = 1;
    }
    s = (date.length() > value.length()) ? date.length() : value.length(); 
    for (int i = s; i >= 0; i--)
    {
        if (!c_date && i < date.length() && std::isspace(date[i]))
        {
            date.erase(i, 1);
        }
        if (!c_value && i < value.length() && std::isspace(value[i]))
        {
            value.erase(i, 1);
        }
    }
}

void BitcoinExchange::process(const char *av)
{
	std::string buffer;
	std::string date;
	std::string value;
    std::fstream in_file(av);
	std::stringstream res;
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
		res.str(buffer);
		getline(res, date, '|');
		getline(res, value);
        remove_whitespace(date, value);
        if (!parse(date, value))
            continue;
        
    }
}

int BitcoinExchange::parse(std::string &date, std::string &value)
{
    std::stringstream res(date);
    float f;
    int c = 0;
    int count = 0;
    int v = 0;
    int k = 0;
    int white_count = 0;
	if (date.size() != 10)
	{
		std::cerr << "Error: bad input => " << date << "\n";
        return (0);
	}
    if (value.find('-') != std::string::npos)
    {
        std::cerr << "Error: not a positive number." << "\n";
        return (0);
    }
	for (size_t i = 0; i < date.size(); i++)
	{
        if (date[i] == '-')
            white_count++;
        if (white_count > 2)
        {
            std::cerr << "Error: bad input => " << date <<"\n";
            return (0);
        }
        if ((i <= 3 || (i > 4 && i < 7) || i > 7) && !std::isdigit(date[i]))
        {
			std::cerr << "Error: bad input => " << date <<"\n";
            return (0);
        }
		if ((i == 4 or i == 7) && date[i] != '-')
		{
			std::cerr << "Error: bad input => " << date <<"\n";
            return (0);
		}
	}
    if (value.empty())
    {
        std::cerr << "Error: empty value => " << value <<"\n";
        return (0);
    }
    for (size_t i = 0; i < value.size(); i++)
	{
        if ((!i && value[i] == '-'))
            continue;
        if (!count && value[i] == '.')
        {
            count++;
            continue;
        }
        

        
    }
    res >> f;
    if (f > 1000)
    {
        std::cerr << "Error: too large a number.\n";
        return (0);
    }

}