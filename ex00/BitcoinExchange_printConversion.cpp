#include "BitcoinExchange.hpp"

void		BitcoinExchange::printConversion(std::string const & date, float value) const
{
	PriceDatabase::const_iterator	it = findClosestRate(date);

	if (it == this->rates_.end())
	{
		std::cerr << "Error: no rate available for the date " << date << std::endl;
		return ;
	}

	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}
