#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const & srs)
{
	(void)srs;
}

PmergeMe &	PmergeMe::operator=(PmergeMe const & rhs)
{
	(void)rhs;
	return *this;
}

PmergeMe::~PmergeMe()
{
}
