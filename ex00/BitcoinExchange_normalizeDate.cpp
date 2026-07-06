#include "BitcoinExchange.hpp"

std::string		BitcoinExchange::normalizeDate(std::string const & date) const
{
	if (date.length() == 10)
		return date;

	std::string normalized = date;
	if (normalized[5] != 0 && normalized[7] != '-')
		normalized.insert(5, "0");

	if (normalized[8] != 0 && normalized.length() < 10)
		normalized.insert(8, "0");

	return normalized;
}

