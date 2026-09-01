#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <vector>
# include <deque>

class PmergeMe {
	private :
		PmergeMe();
		PmergeMe(PmergeMe const & srs);
		PmergeMe&	operator=(PmergeMe const & rhs);
		~PmergeMe();

	public :
		static std::vector<int>		inputParse(int ac, char *av[]);
		static std::deque<int>		vectorToDeque(std::vector<int> const & vec);
		static void					vectorSort(std::vector<int> & vec);
		static void					dequeSort(std::deque<int> & deq);
};

#endif
