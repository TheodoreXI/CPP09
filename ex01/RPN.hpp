#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <sstream>
#include <exception>

class RPN
{
    private:
        std::stack<int> st;
        int res;
    public:
        RPN(void);
        ~RPN(void);
        RPN(std::string &s);
        RPN(const RPN &obj);
        RPN &operator=(const RPN &obj);
        int get_res(void);

};




#endif