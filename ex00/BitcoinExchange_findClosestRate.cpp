#include "BitcoinExchange.hpp"

BitcoinExchange::PriceDatabase::const_iterator	BitcoinExchange::findClosestRate(std::string const & date) const
{
	std::string						normalizedDate = this->normalizeDate(date);
	PriceDatabase::const_iterator	it = this->rates_.lower_bound(normalizedDate);

	if (it != this->rates_.end() && it->first == normalizedDate)
		return it;

	if (it == this->rates_.begin())
		return this->rates_.end();

	--it;
	return it;
}
