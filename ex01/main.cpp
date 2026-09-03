#include "RPN.hpp"
#include <stream>

int main(int ac, char *av[])
{
	if (ac != 2)
		return (std::cout << "Error\n", 1);
	std::cout << RPN::evaluate(av[1]);
	return 0;
}

