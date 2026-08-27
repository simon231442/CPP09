#include "BitcoinExchange.hpp"
#include <fstream>

void BitcoinExchange::loadDatabase(std::string const & databaseFile) 
{
	std::ifstream					file(databaseFile.c_str());
	if (!file.is_open())
		throw std::exception;
	std::string;					line;
	size_t							commaIndex;
	std::string						date;
	std::istringstream				price_stream;
	float							price_float;

	std::getline(file, line);
	while (1)
	{
		std::getline(file, line);
		if (file.eof())
			break;
		commaIndex = line.find(',');
		if (commaIndex == npos)
			continue;
		date = line.substr(0, commaIndex);
		price_stream = line.substr(commaIndex + 1);
		try {
			price_stream >> price_float;
			this->priceDatabase[date] = price_float;
		}
		catch (std::exception const & e)
			continue;
	}
}








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


//2012-07-04,6.71
