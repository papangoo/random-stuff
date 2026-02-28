#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(PmergeMe const & p) {(void) p;}

PmergeMe::~PmergeMe(void) {}

PmergeMe&	PmergeMe::operator=(PmergeMe const & p)
{
	(void) p;

	return (*this);
}

std::vector< std::vector<int> >::iterator	PmergeMe::binary_search(std::vector< std::vector<int> >::iterator first, std::vector< std::vector<int> >::iterator last, int value)
{
	std::vector< std::vector<int> >::iterator	middle;

	while (first < last)
	{
		middle = first + (last - first) / 2;
		if ((*middle)[0] == value)
		{
			return (middle);
		}
		else if ((*middle)[0] < value)
		{
			first = middle + 1;
		}
		else
		{
			last = middle;
		}
	}
	return (first);
}

void	PmergeMe::merge_insertion(std::vector< std::vector<int> > & v)
{
	std::vector< std::vector<int> > v2;

	if (v.size() <= 1)
	{
		return ;
	}

	v2.reserve((v.size() + 1) / 2);
	
	for (int i = 0; i < (int) v.size() - 1; i+=2)
	{
		std::vector<int> v3;

		v3.reserve(v[i].size() + v[i+1].size());
		if (v[i][0] > v[i+1][0])
		{
			v3.insert(v3.end(), v[i].begin(), v[i].end());
			v3.insert(v3.end(), v[i+1].begin(), v[i+1].end());
		}
		else
		{
			v3.insert(v3.end(), v[i+1].begin(), v[i+1].end());
			v3.insert(v3.end(), v[i].begin(), v[i].end());
		}
		v2.push_back(v3);
	}

	merge_insertion(v2);

	if (v.size() & 1)
	{
		v2.push_back(*(v.end() - 1));
	}

	std::vector<int>	tmp(v2[0].begin() + v2[0].size() / 2, v2[0].end());
	int					inserted;
	int					jacob_idx;
	int					r;
	int					to_insert;
	int const			total_to_insert = (int) (v.size() + 1) / 2;

	v2.insert(v2.begin(), tmp);
	inserted = 1;
	v2[1].erase(v2[1].begin() + v2[1].size() / 2, v2[1].end());
	
	jacob_idx = 3;
	while (inserted < total_to_insert)
	{
		r = PmergeMe::vec_jacobsthal_nbs[jacob_idx] - 1 + inserted;
		if (r >= (int) (v2.size()))
		{
			r = v2.size() - 1;
		}
		to_insert = PmergeMe::vec_jacobsthal_nbs[jacob_idx] - PmergeMe::vec_jacobsthal_nbs[jacob_idx - 1];
		if (to_insert > total_to_insert - inserted)
		{
			to_insert = total_to_insert - inserted;
		}
		for (int i = r; to_insert > 0 && i >= 0; --i)
		{
			if (v2[i].size() == v[0].size() * 2)
			{
				std::vector<int>	tmp2(v2[i].begin() + v2[i].size() / 2, v2[i].end());
				v2.insert(binary_search(v2.begin(), v2.begin() + i, tmp2[0]), tmp2);
				v2[i+1].erase(v2[i+1].begin() + v2[i+1].size() / 2, v2[i+1].end());
				++inserted;
				--to_insert;
			}
			else if ((v.size() & 1) && i == (int) v2.size() - 1)
			{
				v2.insert(binary_search(v2.begin(), v2.begin() + i, v2[i][0]), v2[i]);
				v2.erase(v2.begin() + i + 1);
				++inserted;
				--to_insert;
			}
		}
	}

	v = v2;
}

void	PmergeMe::init_jacob(int max_value)
{
	int	i;

	if (PmergeMe::vec_jacobsthal_nbs.size() == 0 && max_value > 1)
	{
		i = 1;
		PmergeMe::vec_jacobsthal_nbs.push_back(0);
		PmergeMe::vec_jacobsthal_nbs.push_back(1);
		while(max_value > PmergeMe::vec_jacobsthal_nbs[i])
		{
			++i;
			PmergeMe::vec_jacobsthal_nbs.push_back(PmergeMe::vec_jacobsthal_nbs[i - 1] + 2 * PmergeMe::vec_jacobsthal_nbs[i - 2]);
		}
	}
}

void	PmergeMe::sort(std::vector<int> & v)
{
	std::vector< std::vector<int> >	V;

	for (int i = 0; i < (int) v.size(); ++i)
	{
		std::vector<int>	temp;
		temp.push_back(v[i]);
		V.push_back(temp);
	}

	init_jacob((v.size() + 1) / 2);

	merge_insertion(V);

	for (int i = 0; i < (int) v.size(); ++i)
	{
		v[i] = V[i][0];
	}

}
