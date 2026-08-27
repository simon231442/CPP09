#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <algorithm>
#include <cstdlib>

class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::deque<int>  _deq;

        void parseInput(int argc, char** argv);
        
        // Algorithme Ford-Johnson pour vector
        void sortVector(std::vector<int>& container);
        
        // Algorithme Ford-Johnson pour deque
        void sortDeque(std::deque<int>& container);

        std::vector<size_t> generateJacobsthal(size_t limit);
        double getTimeInUs(struct timeval start, struct timeval end);


    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();

        void run(int argc, char** argv);

};

#endif