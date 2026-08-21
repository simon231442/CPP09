#include "BitcoinExchange.hpp"

bool		BitcoinExchange::dateIsValid(const std::string &date) const
{
	std::istringstream	ss(date);
	int					year, month, day;
	char				waste;

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	ss >> year >> waste >> month >> waste >> day;

	if (ss.fail() || !ss.eof() || year < 0)
		return false;

	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	
	if (month == 2)
	{
		isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
		if (day > (isLeap ? 29 : 28))
			return false;
	}
	return false;
}

// Une annee bissextile est une annee divisible par 4,
// sauf si elle est divisible par 100 (dans ce cas elle
// doit aussi etre divisible par 400 pour rester bissextile)
