#include <iostream>
#include <sstream>

int main()
{
    std::string word = "-9999999999999999";
    std::stringstream ss;
    int n = 0;
    ss.str(word);
    ss >> n;
    std::cout << "this is the number " << n << "\n";
}