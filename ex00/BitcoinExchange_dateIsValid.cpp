#include "BitcoinExchange"

bool		dateIsValid(const std::string &date) const
{
	int		year, month, day;

	if (date.lenght() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	try {
		year = std::atoi(date.substr(0, 4);
		month = std::atoi(date.substr(5, 2);
		Day = std::atoi(date.substr(7. 2);
	}
	catch (std::out_of_range const & e) {
		return false;



