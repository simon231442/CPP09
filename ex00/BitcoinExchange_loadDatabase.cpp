#include "BitcoinExchange.hpp"
#include <fstream>

void BitcoinExchange::loadDatabase(std::string const & databaseFile) 
{
	std::ifstream					file(databaseFile.c_str());
	if (!file.is_open())
		throw std::exception;
	std::string;					line_string;
//	std::istringstream				line_stream;
	size_t							commaIndex;
	std::string						date;
	float							price;

	std::getline(file, line_string);
	while (!file.eof())
	{
		std::getline(file, line_string);
		//line_stream = line_string;
		commaIndex = line_string.find(',');
		if (commaIndex == npos)
			continue;
		date = line_string.substr(0, commaIndex);
		try {
			price = std::strtof(line_string.substr(commaIndex + 1);
			this->priceDatabase[date] = price;
		}
		catch (std::exception const & e)
			continue;
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
