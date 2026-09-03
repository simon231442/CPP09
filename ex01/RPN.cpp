#include "RPN.hpp"
#include <stack>
#include <sstream>

RPN::RPN() {}
RPN::RPN(RPN const & src) { (void)src; }
RPN		RPN::operator=(RPN const & rhs)
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

	while (!iss.fail())
	{
		iss >> value;
		if (iss.fail())
		{
			iss.clear();
			iss >> op;
			if ((op == '+' || op == '-' || op == '/' || op == '*') && oper(stack, op))
				throw;
		}
		else
			stack.push(value);
	}
	return(stack.top());
}

static int oper(std::stack<int> & stack, char op)
{
	int	valueTop = stack.top();

	if (stack.size() < 2)
		return 1;
	stack.pop();
	if (op == '+')
		valueTop += stack.top();
	else if (op == '-')
		valueTop = stack.top() - valueTop;
	else if (op == '/')
	{
		if (stack.top() == 0)
			return 1;
		valueTop = stack.top() / valueTop;
	}
	else if (op == '*')
		valueTop *= stack.top();
	stack.pop();
	stack.push(valueTop);
	return 0;
}






