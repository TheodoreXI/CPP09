#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <fstream>
#include <exception>
#include <iostream>
#include <sstream>


class BitcoinExchange
{
    private:
        std::map<std::string, float> data;
    public:
        BitcoinExchange(void);
        BitcoinExchange(const BitcoinExchange &obj);
        ~BitcoinExchange(void);
        BitcoinExchange &operator=(const BitcoinExchange &obj);
        void fill(std::string &s);
        void process(const char *av);
		int parse();
};






#endif