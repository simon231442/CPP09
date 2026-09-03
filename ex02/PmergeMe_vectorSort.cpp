#include "PmergeMe.hpp"
#include <algorithm>
#include <stdexcept>

static int const	jacobsthalSequence[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461};
static size_t const	jacobsthalSequenceSize = sizeof(jacobsthalSequence) / sizeof(jacobsthalSequence[0]);

static int	oddCaseHandle(std::vector<int> & container);
static std::vector<std::pair<int, int> >	pairsMake(std::vector<int> const & container);
static std::vector<int>	bigsExtract(std::vector<std::pair<int, int> > const & pairs);
static std::vector<std::pair<int, int> >	pairsAfterRecursMake(std::vector<int> const & bigs, std::vector<std::pair<int, int> > & pairs);
static std::vector<size_t>	indexOrderMake(size_t n);
static size_t	bigCurrentIndexFind(std::vector<int> const & container, int big);
static void	smallInsert(std::vector<int> & container, int small, size_t bound);

void PmergeMe::vectorSort(std::vector<int> & container)												//{4, 9, 8, 2, 7, 6, 4, 8, 11}
{
	if (container.size() <= 1)
		return;

	int	oddOne = oddCaseHandle(container);															//oddone = 11 (mis de cote) // oddOne = -1 (si impair)
	std::vector<std::pair<int, int> >	pairs = pairsMake(container);								//{[9, 4], [8, 2] , [7, 6], [8, 4]
	std::vector<int>	bigs = bigsExtract(pairs);													//{9, 8, 7, 8}

	PmergeMe::vectorSort(bigs);																		//{7, 8, 8, 9}

	std::vector<std::pair<int, int> >	pairsAfterRecurs = pairsAfterRecursMake(bigs, pairs);		//{[7, 6], [8, 2], [8, 4], [9, 4]}
	std::vector<size_t>	order = indexOrderMake(pairsAfterRecurs.size());							//{0, 2, 1, 3}

	for (size_t i = 0; i < order.size(); ++i)
	{
		int	big = pairsAfterRecurs[order[i]].first;//big corespondant au small a inserer			//big = 7			//8
		int	small = pairsAfterRecurs[order[i]].second;//small a inserer								//small = 6			//2
		size_t	bound = bigCurrentIndexFind(bigs, big);//position de big dans bigs					//bound = 0			//2
		smallInsert(bigs, small, bound);															//{6, 7, 8, 8, 9}	//{2, 6, 7, 8, 8, 9}
	}

	if (oddOne != -1)
		smallInsert(bigs, oddOne, bigs.size());

	container = bigs;
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

static std::vector<int>	bigsExtract(std::vector<std::pair<int, int> > const & pairs)
{
	std::vector<int>	bigs;

	for (size_t i = 0; i < pairs.size(); ++i)
		bigs.push_back(pairs[i].first);
	return bigs;
}

static int	smallFind(std::vector<std::pair<int, int> > & pairs, int big);							//recherche le petit qui etais lie au grand

static std::vector<std::pair<int, int> >	pairsAfterRecursMake(std::vector<int> const & bigs, std::vector<std::pair<int, int> > & pairs)
{
	std::vector<std::pair<int, int> >	result;														//construit un nouveau vecteur de pair (ordre par grand de la pair)

	for (size_t k = 0; k < bigs.size(); ++k)
	{
		int	small = smallFind(pairs, bigs[k]);
		result.push_back(std::make_pair(bigs[k], small));
	}
	return result;
}

static int	smallFind(std::vector<std::pair<int, int> > & pairs, int big)
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

static std::vector<size_t>	indexOrderMake(size_t n)
{
	std::vector<size_t>	order;

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

static size_t	bigCurrentIndexFind(std::vector<int> const & bigs, int big)
{
	size_t	low = 0;
	size_t	high = bigs.size();

	while (low < high)
	{
		size_t	mid = low + (high - low) / 2;
		if (bigs[mid] < big)
			low = mid + 1;
		else if (bigs[mid] > big)
			high = mid;
		else
			return mid;
	}
	throw std::logic_error("bigCurrentIndexFind: not found");
}

static void	smallInsert(std::vector<int> & bigs, int small, size_t bound)
{
	size_t	low = 0;
	size_t	high = bound;

	while (low < high)
	{
		size_t	mid = low + (high - low) / 2;
		if (bigs[mid] < small)
			low = mid + 1;
		else
			high = mid;
	}
	bigs.insert(bigs.begin() + low, small);
}
