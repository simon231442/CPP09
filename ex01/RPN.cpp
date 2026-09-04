#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>

RPN::RPN() {}
RPN::RPN(RPN const & src) { (void)src; }
RPN&	RPN::operator=(RPN const & rhs)
{
	(void)rhs;
	return *this;
}
RPN::~RPN() {}

static int oper(std::stack<int> & stack, char op);

int			RPN::evaluate(std::string const & expression)
{
	std::istringstream		iss(expression);
	int						value;
	char					op;
	std::stack<int>			stack;

	iss >> std::ws;
	while (!iss.fail() && iss.peek() != std::char_traits<char>::eof())
	{
		op = static_cast<char>(iss.peek());
		if (op == '+' || op == '-' || op == '/' || op == '*')
		{
			if (oper(stack, op))
				throw std::invalid_argument("Error");
			iss.ignore();
		}
		else
		{
			iss >> value;
			if (iss.fail())
				throw std::invalid_argument("Error");
			stack.push(value);
		}
		iss >> std::ws;
	}
	if (stack.size() != 1)
		throw std::invalid_argument("Error");
	return (stack.top());
}

static int oper(std::stack<int> & stack, char op)
{
	if (stack.size() < 2)
		return 1;

	int	valueTop = stack.top();

	stack.pop();
	if (op == '+')
		valueTop = stack.top() + valueTop;
	else if (op == '-')
		valueTop = stack.top() - valueTop;
	else if (op == '/')
	{
		if (valueTop == 0)
			return 1;
		valueTop = stack.top() / valueTop;
	}
	else if (op == '*')
		valueTop = stack.top() * valueTop;
	stack.pop();
	stack.push(valueTop);
	return 0;
}
