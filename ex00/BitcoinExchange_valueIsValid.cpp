#include "BitcoinExchange.hpp"

bool	BitcoinExchange::valueIsValid(std::string const & value) const
{
	std::istringstream	ss(value);
	float				val;

	ss >> val;

	return (!ss.fail() && ss.eof() && val >= 0 && val <= 1000);
}
