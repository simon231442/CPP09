#include "PmergeMe.hpp"

static int	oddCaseHandle(std::vector<int> & container);
static std::vector<std::pair<int, int> >	pairsMake(std::vector<int> const & container);

void PmergeMe::vectorSort(std::vector<int>& container)
{
	if (container.size() <= 1)
		return;

	int	oddOne = oddCaseHandle(container);
	std::vector<std::pair<int, int> >	pairs = pairsMake(container);

	(void)oddOne;
	(void)pairs;
	// TODO : extraction des grands, recursion, reattach, jacobsthal, insertion
}

static int	oddCaseHandle(std::vector<int> & container)
{
	if (container.size() % 2 == 0)
		return -1;
	int	oddOne = container.back();
	container.pop_back();
	return oddOne;
}

static std::vector<std::pair<int, int> >	pairsMake(std::vector<int> const & container)
{
	std::vector<std::pair<int, int> >	pairs;

	for (size_t i = 0; i < container.size(); i += 2)
	{
		if (container[i] > container[i + 1])
			pairs.push_back(std::make_pair(container[i], container[i + 1]));
		else
			pairs.push_back(std::make_pair(container[i + 1], container[i]));
	}
	return pairs;
}
