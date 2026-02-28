#include "PmergeMe.hpp"
#include <iostream>

std::vector<int> PmergeMe::vec_jacobsthal_nbs;

int	main(void)
{
	std::vector<int> v;

	v.push_back(9);
	v.push_back(4);
	v.push_back(7);
	v.push_back(2);
	v.push_back(5);
	v.push_back(1);
	v.push_back(3);
	// v.push_back(6);
	// v.push_back(8);

	PmergeMe::sort(v);

	for (int i = 0; i < (int) v.size(); ++i)
	{
		std::cout << v[i] << std::endl;
	}
}
