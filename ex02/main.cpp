#include "PmergeMe.hpp"
#include <iostream>
#include <iomanip>
#include <sys/time.h>

static void		printSequence(std::string const & label, std::vector<int> const & seq);
static double	elapsedUs(struct timeval const & start, struct timeval const & end);

int	main(int ac, char *av[])
{
	try
	{
		std::vector<int>	vec = PmergeMe::inputParse(ac, av);
		std::deque<int>		deq = PmergeMe::vectorToDeque(vec);

		printSequence("Before: ", vec);

		struct timeval	start;
		struct timeval	end;

		gettimeofday(&start, NULL);
		PmergeMe::vectorSort(vec);
		gettimeofday(&end, NULL);
		double	vecTime = elapsedUs(start, end);

		gettimeofday(&start, NULL);
		PmergeMe::dequeSort(deq);
		gettimeofday(&end, NULL);
		double	deqTime = elapsedUs(start, end);

		printSequence("After:  ", vec);

		std::cout << std::fixed << std::setprecision(5);
		std::cout << "Time to process a range of " << vec.size()
			<< " elements with std::vector : " << vecTime << " us" << std::endl;
		std::cout << "Time to process a range of " << deq.size()
			<< " elements with std::deque  : " << deqTime << " us" << std::endl;
	}
	catch (std::exception const & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

static void	printSequence(std::string const & label, std::vector<int> const & seq)
{
	std::cout << label;
	for (size_t i = 0; i < seq.size(); ++i)
		std::cout << seq[i] << (i + 1 < seq.size() ? " " : "");
	std::cout << std::endl;
}

static double	elapsedUs(struct timeval const & start, struct timeval const & end)
{
	return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
}
