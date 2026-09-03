#include "RPN.hpp"
#include <iostream>

int main(int ac, char *av[])
{
	int result;

	if (ac != 2)
		return (std::cout << "Error\n", 1);

	try {
		result = RPN::evaluate(av[1]);}
	catch (std::exception const & e) {
		return (std::cout << "Error\n", 1);}

	std::cout << result;
	return 0;
}

