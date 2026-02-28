#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void){}
BitcoinExchange::BitcoinExchange(BitcoinExchange const & b) : _exchange(b._exchange)
{}
BitcoinExchange::~BitcoinExchange(void){};

BitcoinExchange&	BitcoinExchange::operator=(BitcoinExchange const & b)
{
	this->_exchange = b._exchange;

	return (*this);
}

void	BitcoinExchange::read_csv_file(std::string const & file)
{
	std::ifstream	ifs;
	int				line_nb;
	std::string		s;

	ifs.open(file.c_str());
	if (ifs.fail())
	{
		ifs.close();
		throw std::runtime_error("could not open csv file");
	}
	
	line_nb = 0;
	while (getline(ifs, s))
	{
		if (line_nb == 0)
		{
			if (s != "date,exchange_rate")
			{
				ifs.close();
				throw std::runtime_error("csv file header invalid");
			}
		}
		else
		{
			try
			{
				this->_exchange.insert(this->parse_csv_line(s));
			}
			catch (std::exception const & e)
			{
				std::cout << "Warning: " << e.what() << " => " << s << " (" << file << ":" << line_nb + 1 << ")." << std::endl;
			}
		}
		++line_nb;
	}
	ifs.close();
}

void	BitcoinExchange::exchange(std::string const & file) const
{
	std::ifstream					ifs;
	int								line_nb;
	std::string						s;
	std::pair<std::string,float>	query;

	ifs.open(file.c_str());
	if (ifs.fail())
	{
		ifs.close();
		throw std::runtime_error("could not open input file : " + file);
	}
	line_nb = 0;
	while (getline(ifs, s))
	{
		if (line_nb == 0)
		{
			if (s != "date | value")
			{
				ifs.close();
				throw std::runtime_error("input file header invalid");
			}
		}
		else
		{
			try
			{
				query = parse_input_line(s);
				print_exchange(query);
			}
			catch (std::exception const & e)
			{
				std::cout << "Error: " << e.what() << " => " << s << " (" << file << ":" << line_nb + 1 << ")." << std::endl;
			}
		}
		++line_nb;
	}
	ifs.close();
}

void	BitcoinExchange::print_exchange(std::pair<std::string,float> const & query) const 
{
	float	res;
	std::map<std::string, float>::const_iterator	l_bound;

	l_bound = this->_exchange.lower_bound(query.first);
	if (l_bound->first != query.first)
	{
		if (l_bound == this->_exchange.begin())
		{
			throw std::runtime_error("bitcoins did not exist at that time");
		}
		else
		{
			l_bound--;
		}
	}
	res = query.second * l_bound->second;
	std::cout << query.first << " => " << query.second << " = " << res << std::endl; 
}

std::pair<std::string,float>	BitcoinExchange::parse_csv_line(std::string const & line)
{
	std::string	date;
	float		val;

	date = read_date(line, ",");
	val = read_val(line, ",");

	return (std::make_pair(date, val));
}

std::pair<std::string,float>	BitcoinExchange::parse_input_line(std::string const & line)
{
	std::string	date;
	float		val;

	date = read_date(line, " | ");
	val = read_val(line, " | ");

	if (val > 1000.f)
	{
		throw std::runtime_error("too large number");
	}

	return (std::make_pair(date, val));
}


std::string	BitcoinExchange::read_date(std::string const & line, std::string const & sep)
{
	size_t		pos;
	size_t		start;
	std::string	date;
	std::string syear;
	int			year;
	std::string	smonth;
	int			month;
	std::string	sday;
	int			day;
	
	try
	{
		pos = line.find(sep, 0);
		if (pos == std::string::npos || pos == 0)
		{
			throw std::exception();
		}
		date = line.substr(0, pos);
		
		pos = date.find("-", 0);
		if (pos == std::string::npos || pos == 0)
		{
			throw std::exception();
		}
		syear = date.substr(0, pos);
		if (!isdigit(syear[0]))
		{
			throw std::exception();
		}
		year = stoi(syear);
	
		start = pos + 1;
		pos = date.find("-", start);
		if (pos == std::string::npos || pos == start)
		{
			throw std::exception();
		}
		smonth = date.substr(start, pos - start);
		month = stoi(smonth);
		if (!isdigit(smonth[0]) || smonth.size() != 2 || month < 1 || month > 12)
		{
			throw std::exception();
		}
	
		start = pos + 1;
		sday = date.substr(start);
		day = stoi(sday);
		if (!isdigit(sday[0]) || sday.size() != 2 || day < 1 || day > get_days_in_month(month, year))
		{
			throw std::exception();
		}
	}
	catch (std::exception const & e)
	{
		throw std::runtime_error("invalid date");
	}

	return (date);
}

float BitcoinExchange::read_val(std::string const & line, std::string const & sep)
{
	size_t		pos;
	size_t		start;
	std::string	sval;
	float		val;


	pos = line.find(sep, 0);
	if (pos == std::string::npos)
	{
		throw std::runtime_error("invalid value format");
	}

	start = pos + sep.size();
	if (start >= line.size())
	{
		throw std::runtime_error("invalid value format");
	}

	sval = line.substr(start);
	val = stof(sval);

	return (val);
}

int	BitcoinExchange::stoi(std::string const & s)
{
	const char*	nptr;
	long		val;
	char*		endptr;

	nptr = s.c_str();
	val = strtol(nptr, &endptr, 10);
	if (s.size() == 0 || *endptr != 0 || val < 0L || val > static_cast<long>(INT_MAX))
	{
		throw std::exception();
	}
	return (static_cast<int>(val));
}

float	BitcoinExchange::stof(std::string const & s)
{
	const char*	nptr;
	float		val;
	char*		endptr;

	nptr = s.c_str();
	val = strtof(nptr, &endptr);
	if (s.size() == 0 || *endptr != 0 || isinf(val) || isnan(val))
	{
		throw std::runtime_error("invalid value format");
	}
	else if (val < 0.f)
	{
		throw std::runtime_error("not a positive number");
	}
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (i == 0)
		{
			if (s[i] != '+' && !isdigit(s[i]))
			{
				throw std::runtime_error("invalid value format");
			}
		}
		else
		{
			if (!isdigit(s[i]) && s[i] != '.')
			{
				throw std::runtime_error("invalid value format");
			}
		}
	}
	return (val);
}

int	BitcoinExchange::get_days_in_month(int monthidx, int year)
{
	static std::map<int,int>	days_in_month;

	if (days_in_month.empty())
	{
		days_in_month.insert(std::make_pair(1, 31));
		days_in_month.insert(std::make_pair(3, 31));
		days_in_month.insert(std::make_pair(4, 30));
		days_in_month.insert(std::make_pair(5, 31));
		days_in_month.insert(std::make_pair(6, 30));
		days_in_month.insert(std::make_pair(7, 31));
		days_in_month.insert(std::make_pair(8, 31));
		days_in_month.insert(std::make_pair(9, 30));
		days_in_month.insert(std::make_pair(10, 31));
		days_in_month.insert(std::make_pair(11, 30));
		days_in_month.insert(std::make_pair(12, 31));
	}

	if (monthidx < 1 || monthidx > 12 || year < 0)
	{
		return (0);
	}
	if (monthidx == 2)
	{
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		{
			return (29);
		}
		return (28);
	}
	return (days_in_month[monthidx]);
}
