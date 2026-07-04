#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>

void BitcoinExchange::loadDatabase(std::string const & databaseFile) 
{
	std::string		line;
	std::string		date;
	std::string		price;

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
		price = line.substr(commaPos + 1);




