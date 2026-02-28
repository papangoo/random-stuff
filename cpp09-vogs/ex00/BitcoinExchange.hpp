#ifndef BITCOINEXCHANGE_CPP
# define BITCOINEXCHANGE_CPP

# include <map>
# include <string>
# include <fstream>
# include <exception>
# include <cstdlib>
# include <climits>
# include <cmath>
# include <iostream>

class BitcoinExchange
{
private:
	std::map<std::string,float>			_exchange;
	
public:
	BitcoinExchange(void);
	BitcoinExchange(BitcoinExchange const & b);
	~BitcoinExchange(void);

	BitcoinExchange&					operator=(BitcoinExchange const & b);

	void								read_csv_file(std::string const & file);
	void								exchange(std::string const & input_file) const;
	void								print_exchange(std::pair<std::string,float> const & query) const;

	static std::pair<std::string,float>	parse_csv_line(std::string const & line);
	static std::pair<std::string,float> parse_input_line(std::string const & line);
	static std::string					read_date(std::string const & line, std::string const & sep);
	static float						read_val(std::string const & line, std::string const & sep);
	static int							stoi(std::string const & s);
	static float						stof(std::string const & s);
	static int							get_days_in_month(int monthidx, int year);
};

#endif
