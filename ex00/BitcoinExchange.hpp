#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <string>
# include <stdlib>

class BitcoinExchange {
public:
	typedef std::map<std::string, float>	PriceDatabase;

	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &rhs);
	~BitcoinExchange();
	BitcoinExchange&						operator=(const BitcoinExchange &rhs);

	void loadDatabase(const std::string &databaseFile);
	void processInput(const std::string &inputFile) const;

private:
	PriceDatabase							rates_;

	bool							dateIsValid(const std::string &date) const;
	bool 							isValidValue(const std::string &value) const;
	std::string						trim(const std::string &text) const;
	std::string						normalizeDate(const std::string &date) const;
	PriceDatabase::const_iterator	findClosestRate(const std::string &date) const;
	void							printConversion(const std::string &date, float value) const;
};

#endif
