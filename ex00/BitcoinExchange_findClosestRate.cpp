#include "BitcoinExchange.hpp"

BitcoinExchange::PriceDatabase::const_iterator	BitcoinExchange::findClosestRate(std::string const & date) const
{
	std::string						normalizedDate = this->normalizeDate(date);
	PriceDatabase::const_iterator	it = this->rates_.lower_bound(normalizedDate);

	if (it != this->rates_.begin() && it == this->rates_.end())
	{
		if (it->first != normalizedDate)
			--it;
	}

	return it;
}

