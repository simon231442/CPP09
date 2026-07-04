#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>
#include <cstdlib>

void BitcoinExchange::loadDatabase(std::string const & databaseFile) 
{
	std::string		line;
	std::string		date;
	std::string		priceStr;
	float			price;

	std::ifstream	file(databaseFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Couldn't open the database file");
	
	std::getline(file, line);

	while(std::getline(file, line))
	{
		size_t	commaPos = line.find(',');
		if (commaPos == std::string::npos)
			continue;
		date = line.substr(0, commaPos);
		priceStr = line.substr(commaPos + 1);
		date = trim(date);
		priceStr = trim(priceStr);

		try {
			price = std::strtof(priceStr.c_str(), NULL);
			this->rates_[date] = price;
		}
		catch (std::exception const &e) {
			continue ;
		}
	}
}


