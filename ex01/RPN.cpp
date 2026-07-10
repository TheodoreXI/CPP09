#include "RPN.hpp"

RPN::RPN(void)
    :res(0)
{
}

RPN::~RPN(void)
{
}

int ft_parse(char c, int num1, int num2)
{
    if (c == '+')
        return (num1+num2);
    else if (c == '-')
        return (num1-num2);
    else if (c == '*')
        return (num1*num2);
    else if (c == '/')
        return (num1/num2);
    else
        throw (std::runtime_error("Error"));
}

RPN::RPN(std::string &s)
{
    std::stringstream str(s);
    std::string word;
    int ele = 0;
    int num1 = 0;
    int num2 = 0;
    while (str >> word)
    {
        if (word.size() == 1)
        {
            if (isdigit(word[0]))
            {
                ele = word[0] - '0';
                st.push(ele);
            }
            else if (word[0] == '/' || word[0] == '*' || word[0] == '-' || word[0] == '+')
            {
                if (st.size() < 2)
                    throw (std::runtime_error("Error"));
                num2 = st.top();
                st.pop();
                num1 = st.top();
                st.pop();
                res = ft_parse(word[0], num1, num2);
                st.push(res);
            }
        }
        else
        {
            throw (std::runtime_error("Error"));
        }
    }
    if (st.size() > 1)
        throw (std::runtime_error("Error"));
    res = st.top();
    st.pop();

}

RPN::RPN(const RPN &obj)
{
    *this = obj;
}

RPN &RPN::operator=(const RPN &obj)
{
    if (this != &obj)
    {
        this->res = obj.res;
        this->st = obj.st;
    }
    return (*this);
}

int RPN::get_res(void)
{
    return (res);
}