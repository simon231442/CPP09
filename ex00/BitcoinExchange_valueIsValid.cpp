#include "BitcoinExchange.hpp"

bool	BitcoinExchange::ValueIsValid(std::string const & value) const
{
	size_t		i = 0;
	bool		hasDecimal = false;
	char*		end;

	if (value.is_empty())
		return false;
	
	if (value[i] == '-')
		return false;

	for (; i < value.size(); ++i)
	{
		if (value[i] == '.')
		{
			if (hasDecimal)
			{
				return false;
				hasDecimal = true;
			}
		}
		else if (!isdigit(value[i]))
			return false;
	}

	if (hasDecimal && (value[0] == '.' || value[value.size() -1]))
		return false;
	
