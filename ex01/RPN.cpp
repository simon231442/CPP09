#include <stream>

RPN::RPN() {}
RPN::RPN(RPN const & src) { void src }
RPN		RPN::operateur=(RPN const & rhs)
{
	(void)rhs;
	return *this;
}
RPN::~RPN() {}

static int	oper(std::stack<int> & stack, char op);

int			RPN::evaluate(std::string const & expression)
{
	std::istringstream		iss(expression);
	int						value;
	char					op;
	std::stack<int>			stack;

	while (!iss.empty())
	{
		iss >> value;
		if (iss.fail)
		{
			iss >> op;
			if (op == '+' || op == '-' || op == '/' || op == '*')
				oper(stack, op);
		}
		stack.push(value);
	}
	return(stack.top());
}

int	oper(std::stack<int> & stack, char op)
{
	int	valueTop = stack.top();
	stack.pop();
	if (op == '+')
		ValueTop += stack.top();
	else if (op == '-')
		ValueTop = stack.top() - valueTop;
	else if (op == '/')
		ValueTop = stack.top() / valueTop;
	else if (op == '*')
		ValueTop *= stack.top();
	stack.pop();
	stack.push(valueTop);
}






