#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>
# include <climits>
# include <iostream>

class RPN
{
private:
	RPN(void);
	RPN(RPN const & rpn);
	~RPN(void);
	RPN&	operator=(RPN const & rpn);
	static bool		is_operator(char c);
	static int		compute(char oper, int val1, int val2);

public:
	static int		evaluate(std::string const & expr);
};

#endif
