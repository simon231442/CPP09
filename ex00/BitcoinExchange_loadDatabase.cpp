#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>

void BitcoinExchange::loadDatabase(std::string const & databaseFile) 
{
	std::string		line;
	std::string		date;
	std::string		priceStr;
	flaot			price;

	std::ifstream	file(databaseFile.str());
	if (!file.is_open())
		throw std::runtime_error("Couldn't open the database file");
	
	std::getline(file, line);

	while(std::getline(file, line))
	{
		size_t	commaPos = line.find(',');
		if (commaPos == std::string::nopos)
			continue;
		date = line.substr(0, commaPos);
		priceStr = line.substr(commaPos + 1);
		date = trim(date);
		priceStr = trim(priceStr;

		try {
			price = std::stof(priceStr);
			this->rates_[date] = price;
		}
		catch {
			continue ;


