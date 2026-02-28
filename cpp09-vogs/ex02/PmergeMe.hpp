#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <set>
# include <cstddef>
# include <algorithm>

class PmergeMe
{
private:
	static std::vector<int>	vec_jacobsthal_nbs;

	PmergeMe(void);
	PmergeMe(PmergeMe const & p);
	~PmergeMe(void);
	PmergeMe&	operator=(PmergeMe const & p);
	template <typename Container>
	static bool	is_valid(Container const & v);
	template<typename T>
	static T	min(T a, T b);
	template<typename T>
	static T	max(T a, T b);
	static void	init_jacob(int n);
	static void	merge_insertion(std::vector< std::vector<int> > & v);
	static std::vector< std::vector<int> >::iterator	binary_search(std::vector< std::vector<int> >::iterator first, std::vector< std::vector<int> >::iterator last, int value);

public:
	static void					sort(std::vector<int> & v);
};


template<typename T>
T	PmergeMe::min(T a, T b)
{
	if (a < b)
	{
		return (a);
	}
	return (b);
}

template<typename T>
T	PmergeMe::max(T a, T b)
{
	if (a > b)
	{
		return (a);
	}
	return (b);
}

template <typename Container>
bool	PmergeMe::is_valid(Container const & c)
{
	std::set<int>	s;

	for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
	{
		if (*it <= 0) // ! <= or <
		{
			return (false);
		}
		if (s.count(*it) > 0)
		{
			return (false);
		}
		s.insert(*it);
	}
	return (true);
}

#endif


//	A : (5,-1) (4,-1) (3,-1) (1,-1)
// 		A : (5,4) (3,1)
//			A : (5,3)
//			R : (5,3)
//		R : (3,1) (5,2)

