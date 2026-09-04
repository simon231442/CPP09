#include "BitcoinExchange.hpp"
#include <fstream>

void	BitcoinExchange::processInput(std::string const & inputFile) const
{
	std::ifstream	file(inputFile.c_str());
	std::string		line;
	std::string		date;
	std::string		valueStr;
	float			value;

	if (!file.is_open())
		throw std::runtime_error("Couldn't open the inputs file");

	std::getline(file, line); // skip header line ("date | value")

	while (std::getline(file, line))
	{
		size_t	pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		date = trim(line.substr(0, pipePos));
		valueStr = trim(line.substr(pipePos + 1));

		if (!dateIsValid(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		if (!valueIsValid(valueStr))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}

		value = std::strtof(valueStr.c_str(), NULL);

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		printConversion(date, value);
	}
}
