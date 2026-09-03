#include <stream>

RPN::RPN() {}
RPN::RPN(RPN const & src) { void src }
RPN		RPN::operateur=(RPN const & rhs)
{
	(void)rhs;
	return *this;
}
RPN::~RPN() {}

int		RPN::evaluate(std::string const & expression)
{
	std::istringstream		iss(expression);
	int						value;
	char					operal;

	while (iss)
	{
		try (iss >> value)
		catch (


