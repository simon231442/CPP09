#include "PmergeMe.hpp"
#include <sstream>

static int	toPositiveInt(std::string const & token);

std::vector<int>	PmergeMe::inputParse(int ac, char *av[])
{
	std::vector<int>	result;

	if (ac < 2)
		throw std::invalid_argument("Error");

	for (int i = 1; i < ac; ++i)
		result.push_back(toPositiveInt(av[i]));

	return result;
}

static bool	extractInt(std::string const & token, int & value);

static int	toPositiveInt(std::string const & token)
{
	int	value;

	if (!extractInt(token, value))
		throw std::invalid_argument("Error");
	if (value <= 0)
		throw std::invalid_argument("Error");
	return value;
}

static bool	extractInt(std::string const & token, int & value)
{
	std::istringstream	ss(token);

	ss >> value;
	return (!ss.fail() && ss.eof());
}
