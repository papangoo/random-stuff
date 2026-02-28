#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Error: not enough arguments." << std::endl;
		return (1);
	}
	else if (argc != 2)
	{
		std::cout << "Error: too much arguments." << std::endl;
		return (1);
	}

	BitcoinExchange bit_ex;
	std::string		csv_file("data.csv");
	std::string		input_file(argv[1]);

	try
	{
		bit_ex.read_csv_file(csv_file);
		bit_ex.exchange(input_file);
	}
	catch (std::exception const & e)
	{
		std::cout << "Error: " << e.what() << "." << std::endl;
		return (1);
	}

	return (0);
}
