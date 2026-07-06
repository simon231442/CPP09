#include "BitcoinExchange.hpp"

void		BitcoinExchange::printConversion(std::string const & date, float value) const
{
	PriceDatabase::const_iterator	it;
	float							rate;

	it = findClosestRate(date);
	
