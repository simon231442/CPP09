#include "BitcoinExchange.hpp"

bool		dateIsValid(const std::string &date) const
{
	int		year, month, day;
	bool	isLeap;

	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	try {
		year = std::atoi(date.substr(0, 4).c_str());
		month = std::atoi(date.substr(5, 2).c_str());
		day = std::atoi(date.substr(8, 2).c_str());
	}
	catch (std::out_of_range const & e) {
		return false;
	}
	
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
	return true;
}




