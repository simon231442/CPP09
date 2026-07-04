#include "BitcoinExchange.hpp"
#include <fstream>

void	BitcoinExchange::processInput(std::string const & inputFile) const
{
	std::ifstream file(inputFile.c_str());

	if (!file.is_open())
		throw std::runtime_error("Couldn't open the database file");
	
	std::getline(file, line);

	while(std::getline(file, line))
	{
		size_t	pipePos = line.find('|');
		if (pipePos == std::string::npos)
			continue;
		date = line.substr(0, pipePos);
		priceStr = line.substr(pipePos + 1);
		date = trim(date);
		priceStr = trim(priceStr);

		try {

	

	
