#include "BitcoinExchange.hpp"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "You need to input " << argv[0] << " then the name of the file.\n";
    }
    std::string buffer;
    std::fstream in_file(argv[1]);
    if (!in_file.is_open())
    {
        throw (std::runtime_error("Could not open file.\n"));
    }
	

}