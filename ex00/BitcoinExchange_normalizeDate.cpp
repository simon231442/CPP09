#include "BitcoinExchange.hpp"

std::string		BitcoinExchange::normalizeDate(std::string const & date) const
{
	std::string	result = date;
	size_t		firstDash = result.find('-');

	if (firstDash == std::string::npos)
		return result;

	size_t		secondDash = result.find('-', firstDash + 1);

	if (secondDash == std::string::npos)
		return result;

	std::string	year = result.substr(0, firstDash);
	std::string	month = result.substr(firstDash + 1, secondDash - firstDash - 1);
	std::string	day = result.substr(secondDash + 1);

	if (month.length() == 1)
		month = "0" + month;
	if (day.length() == 1)
		day = "0" + day;

	return year + "-" + month + "-" + day;
}
