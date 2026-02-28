#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Invalid number of arguments" << std::endl;
		
		return (1);
	}

	std::string	expr(argv[1]);
	int			ans;

	try
	{
		ans = RPN::evaluate(expr);
		std::cout << ans << std::endl;
	}
	catch (std::runtime_error const & e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	catch (std::exception const & e)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	return (0);
}
