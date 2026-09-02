#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>

static int const	jacobsthalSequence[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};
static size_t const	jacobsthalSequenceSize = sizeof(jacobsthalSequence) / sizeof(jacobsthalSequence[0]);

static int	oddCaseHandle(std::deque<int> & container);
static std::deque<std::pair<int, int> >	pairsMake(std::deque<int> const & container);
static std::deque<int>	bigsExtract(std::deque<std::pair<int, int> > const & pairs);
static std::deque<std::pair<int, int> >	pairsAfterRecursMake(std::deque<int> const & bigs, std::deque<std::pair<int, int> > & pairs);
static std::deque<size_t>	indexOrderMake(size_t n);
static size_t	bigCurrentIndexFind(std::deque<int> const & container, int big);
static void	smallInsert(std::deque<int> & container, int small, size_t bound);

void PmergeMe::dequeSort(std::deque<int> & container)
{
	if (container.size() <= 1)
		return;

	int	oddOne = oddCaseHandle(container);
	std::deque<std::pair<int, int> >	pairs = pairsMake(container);
	std::deque<int>	bigs = bigsExtract(pairs);

	PmergeMe::dequeSort(bigs);

	std::deque<std::pair<int, int> >	pend = pairsAfterRecursMake(bigs, pairs);
	std::deque<size_t>	order = indexOrderMake(pend.size());

	for (size_t i = 0; i < order.size(); ++i)
	{
		size_t	idx = order[i];
		int	big = pend[idx].first;
		int	small = pend[idx].second;
		size_t	bound = bigCurrentIndexFind(bigs, big);
		smallInsert(bigs, small, bound);
	}

	if (oddOne != -1)
		smallInsert(bigs, oddOne, bigs.size());

	container = bigs;
}

static int	oddCaseHandle(std::deque<int> & container)
{
	if (container.size() % 2 == 0)
		return -1;
	int	oddOne = container.back();
	container.pop_back();
	return oddOne;
}

static std::deque<std::pair<int, int> >	pairsMake(std::deque<int> const & container)
{
	std::deque<std::pair<int, int> >	pairs;

	for (size_t i = 0; i < container.size(); i += 2)
	{
		if (container[i] > container[i + 1])
			pairs.push_back(std::make_pair(container[i], container[i + 1]));
		else
			pairs.push_back(std::make_pair(container[i + 1], container[i]));
	}
	return pairs;
}

static std::deque<int>	bigsExtract(std::deque<std::pair<int, int> > const & pairs)
{
	std::deque<int>	bigs;

	for (size_t i = 0; i < pairs.size(); ++i)
		bigs.push_back(pairs[i].first);
	return bigs;
}

static int	smallFind(std::deque<std::pair<int, int> > & pairs, int big);

static std::deque<std::pair<int, int> >	pairsAfterRecursMake(std::deque<int> const & bigs, std::deque<std::pair<int, int> > & pairs)
{
	std::deque<std::pair<int, int> >	result;

	for (size_t k = 0; k < bigs.size(); ++k)
	{
		int	small = smallFind(pairs, bigs[k]);
		result.push_back(std::make_pair(bigs[k], small));
	}
	return result;
}

static int	smallFind(std::deque<std::pair<int, int> > & pairs, int big)
{
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		if (pairs[i].first == big)
		{
			int	small = pairs[i].second;
			pairs.erase(pairs.begin() + i);
			return small;
		}
	}
	throw std::logic_error("smallFind: no match");
}

static std::deque<size_t>	indexOrderMake(size_t n)
{
	std::deque<size_t>	order;

	if (n == 0)
		return order;
	order.push_back(0);
	size_t	prev = 1;
	for (size_t j = 1; j < jacobsthalSequenceSize && prev < n; ++j)
	{
		size_t	high = std::min(static_cast<size_t>(jacobsthalSequence[j]), n);
		for (size_t t = high; t > prev; --t)
			order.push_back(t - 1);
		prev = high;
	}
	return order;
}

static size_t	bigCurrentIndexFind(std::deque<int> const & container, int big)
{
	size_t	low = 0;
	size_t	high = container.size();

	while (low < high)
	{
		size_t	mid = low + (high - low) / 2;
		if (container[mid] < big)
			low = mid + 1;
		else if (container[mid] > big)
			high = mid;
		else
			return mid;
	}
	throw std::logic_error("bigCurrentIndexFind: not found");
}

static void	smallInsert(std::deque<int> & container, int small, size_t bound)
{
	size_t	low = 0;
	size_t	high = bound;

	while (low < high)
	{
		size_t	mid = low + (high - low) / 2;
		if (container[mid] < small)
			low = mid + 1;
		else
			high = mid;
	}
	container.insert(container.begin() + low, small);
}
