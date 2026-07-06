#include "BitcoinExchange.hpp"
#include <fstream>

void	BitcoinExchange::processInput(std::string const & inputFile) const
{
	std::ifstream	file(inputFile.c_str());
	std::string		valueStr;
	std::string		date;
	float			value;

	if (!file.is_open())
		throw std::runtime_error("Couldn't open the inputs file");
	
	std::getline(file, line);

	while(std::getline(file, line))
	{
		size_t	pipePos = line.find('|');
		if (pipePos == std::string::npos)
			continue;
		date = line.substr(0, pipePos);
		valueStr = line.substr(pipePos + 1);
		date = trim(date);
		valueStr = trim(valueStr);

		if ((this->dateIsValid(date)) || (this->valueIsValid(valueStr))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		value = std::strtof(valueStr.c_str(), NULL);

		try {
			this->printConversion(date, value);
		}
		catch (std::exception const e)

	

	
