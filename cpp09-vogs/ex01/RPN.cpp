#include "RPN.hpp"

RPN::RPN(void) {}

RPN::RPN(RPN const & rpn) {(void) rpn;}

RPN::~RPN(void) {}

RPN&	RPN::operator=(RPN const & rpn)
{
	(void) rpn;
	return (*this);
}

bool		RPN::is_operator(char c)
{
	return (c == '-' || c == '+' || c == '*' || c == '/');
}

int			RPN::compute(char oper, int val1, int val2)
{
	long	res;
	switch (oper)
	{
	case '+':
		res = static_cast<long>(val1) + static_cast<long>(val2);
		if (res < INT_MIN || res > INT_MAX)
		{
			throw std::runtime_error("overflow / underflow");
		}
		return (static_cast<int>(res));
	case '-':
		res = static_cast<long>(val1) - static_cast<long>(val2);
		if (res < INT_MIN || res > INT_MAX)
		{
			throw std::runtime_error("overflow / underflow");
		}
		return (static_cast<int>(res));
	case '*':
		res = static_cast<long>(val1) * static_cast<long>(val2);
		if (res < INT_MIN || res > INT_MAX)
		{
			throw std::runtime_error("overflow / underflow");
		}
		return (static_cast<int>(res));
	case '/':
		if (val2 == 0)
			throw std::runtime_error("division by 0");
		return (val1 / val2);
	default:
		throw std::exception();
	}
}

int	RPN::evaluate(std::string const & expr)
{
	std::stack<int>	s;
	size_t			i;
	int				val1;
	int				val2;

	i = 0;
	while (i < expr.size())
	{
		while (isspace(expr[i]))
		{
			++i;
		}
		if (i < expr.size())
		{
			if (isdigit(expr[i]))
			{
				s.push(static_cast<int>(expr[i] - '0'));
			}
			else if (is_operator(expr[i]))
			{
				if (s.size() < 2)
				{
					throw std::exception();
				}
				val2 = s.top();
				s.pop();
				val1 = s.top();
				s.pop();
				s.push(compute(expr[i], val1, val2));
			}
			else
			{
				throw std::exception();
			}

			++i;
			if (i < expr.size() && !isspace(expr[i]))
			{
				throw std::exception();
			}
		}
	}
	if (s.size() != 1)
	{
		throw std::exception();
	}
	else
	{
		return (s.top());
	}
}
