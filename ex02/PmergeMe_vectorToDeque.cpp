#include "PmergeMe.hpp"

std::deque<int>	PmergeMe::vectorToDeque(std::vector<int> const & vec)
{
	return std::deque<int>(vec.begin(), vec.end());
}
