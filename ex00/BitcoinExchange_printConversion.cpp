#include "BitcoinExchange.hpp"

void		BitcoinExchange::printConversion(std::string const & date, float value) const
{
	PriceDatabase::const_iterator	it;
	float							rate;

	it = findClosestRate(date);
	if (this->rates_.end() == it && it->first != this->normalizeDate(date))
	{
		std::cerr << "Error: no rate aviable for the date " << date << std::endl;
		return ;
	}

	std::cout << date << " => " << value << " = " << value * rate;
}
	
