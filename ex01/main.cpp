#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error\n";
        return (1);
    }
    std::string s(av[1]);
    try
    {
        RPN r(s);
        std::cout << "HERE " << r.get_res() << "\n";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}