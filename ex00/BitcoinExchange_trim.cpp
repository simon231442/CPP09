#include "BitcoinExchange.hpp"

std::string		BitcoinExchange::trim(std::string const & text) const
{
	size_t		start;
	size_t		end;

	start = text.find_first_not_of(" \t");
	if (start == std::string::npos)
		return "";
	end = text.find_last_not_of(" \t");

	return text.substr(start, end - start + 1);
}
