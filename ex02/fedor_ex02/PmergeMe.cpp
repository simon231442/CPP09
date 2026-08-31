#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe& other)
{
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    if (this != &other) {
        this->_vec = other._vec;
        this->_deq = other._deq;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{

}

double PmergeMe::getTimeInUs(struct timeval start, struct timeval end)
{
    // Convertit la difference de temps en microsecondes.
    return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
}

// Lit les arguments, les valide, puis remplit le vector et le deque.
void PmergeMe::parseInput(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.empty())
            throw std::invalid_argument("Error argv est vide");

        // Chaque caractere doit etre numerique.
        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Error");
        }
        long val = std::atol(arg.c_str());
        // On refuse les valeurs hors intervalle d'un int signe positif.
        if (val <= 0 || val > 2147483647)
            throw std::invalid_argument("Error");
        _vec.push_back(static_cast<int>(val));
        _deq.push_back(static_cast<int>(val));
    }
}

// Genere la suite de Jacobsthal jusqu'a la limite demandee.
std::vector<size_t> PmergeMe::generateJacobsthal(size_t limit)
{
    std::vector<size_t> jacob;
    if (limit == 0)
        return jacob;
    jacob.push_back(1);
    if (limit == 1)
        return jacob;
    jacob.push_back(3);
    while (jacob.back() < limit)
    {
        size_t next = jacob.back() + 2 * jacob[jacob.size() - 2];
        jacob.push_back(next);
    }
    return jacob;
}

void PmergeMe::sortVector(std::vector<int>& container)
{
    // Cas de base : un tableau de taille 0 ou 1 est deja trie.
    if (container.size() <= 1)
        return;

    // Si le nombre d'elements est impair, on garde le dernier a part.
    bool hasStraggler = (container.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler != 0)
    {
        // Cet element sera reintegre a la fin par insertion dichotomique.
        straggler = container.back();
        container.pop_back();
    }

    // On construit des paires en plaquant le plus grand element en premier.
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (container[i] > container[i + 1])
            pairs.push_back(std::make_pair(container[i], container[i + 1]));
        else
            pairs.push_back(std::make_pair(container[i + 1], container[i]));
    }

    //-----------------------------------------------------------

    // On separe les grands elements (main chain) des petits (pend).
    // La recursion trie d'abord la main chain, puis les petits sont reinsertes.
    std::vector<int> mainChain;
    std::vector<int> pend;

    // On extrait tous les grands elements dans une chaine temporaire.
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);

    // On trie recursivement les grands elements.
    sortVector(mainChain);

    // On associe a chaque grand son petit element pour reconstruire pend.
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            // On retrouve la paire d'origine grace a la valeur du grand element.
            if (mainChain[i] == pairs[j].first)
            {
                // Le petit element de cette paire va dans pend.
                pend.push_back(pairs[j].second);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }
    //-----------------------------------------------------------

    if (pend.empty() == false)
        mainChain.insert(mainChain.begin(), pend[0]);

    //-----------------------------------------------------------
    // La suite de Jacobsthal donne l'ordre d'insertion des elements de pend.
    // L'objectif est de limiter le nombre de comparaisons.
    std::vector<size_t> jacob = generateJacobsthal(pend.size());
    size_t lastIdx = 1;
    //-----------------------------------------------------------

    for (size_t i = 1; i < jacob.size(); ++i)
    {
        // On prend la derniere position autorisee par Jacobsthal.
        size_t targetIdx = jacob[i] - 1;
        if (targetIdx >= pend.size())
            targetIdx = pend.size() - 1;

        // On insere les elements de pend dans l'ordre inverse du bloc courant.
        for (size_t j = targetIdx; j >= lastIdx; --j)
        {
            // lower_bound renvoie la premiere position ou pend[j] peut aller
            // sans casser l'ordre. La recherche est binaire en interne.
            std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
            mainChain.insert(it, pend[j]);
            if (j == lastIdx)
                break;
        }

        // On memorise le prochain bloc a traiter.
        lastIdx = targetIdx + 1;
        if (lastIdx >= pend.size())
            break;
    }

    // Si un element impair restait, on l'insere comme les autres.
    if (hasStraggler)
    {
        std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }

    container = mainChain;
}

void PmergeMe::sortDeque(std::deque<int>& container)
{
    // Cas de base : un deque de taille 0 ou 1 est deja trie.
    if (container.size() <= 1)
        return;

    // Si le nombre d'elements est impair, on garde le dernier a part.
    bool hasStraggler = (container.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) 
    {
        straggler = container.back();
        container.pop_back();
    }

    // On construit des paires avec le plus grand element en premier.
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (container[i] > container[i + 1])
            pairs.push_back(std::make_pair(container[i], container[i + 1]));
        else
            pairs.push_back(std::make_pair(container[i + 1], container[i]));
    }

    // On isole les grands elements dans mainChain.
    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);

    // Tri recursif de la main chain.
    sortDeque(mainChain);

    // Reconstruction de pend a partir des paires d'origine.
    std::deque<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (mainChain[i] == pairs[j].first)
            {
                pend.push_back(pairs[j].second);
                pairs.erase(pairs.begin() + j);
                break;
            }
        }
    }


    if (!pend.empty())
        mainChain.push_front(pend[0]);

    // Ordre d'insertion guide par la suite de Jacobsthal.
    std::vector<size_t> jacob = generateJacobsthal(pend.size());
    size_t lastIdx = 1;

    for (size_t i = 1; i < jacob.size(); ++i)
    {
        // Fin du bloc courant dans pend.
        size_t targetIdx = jacob[i] - 1;
        if (targetIdx >= pend.size())
            targetIdx = pend.size() - 1;

        for (size_t j = targetIdx; j >= lastIdx; --j)
        {
            std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
            mainChain.insert(it, pend[j]);
            if (j == lastIdx)
                break;
        }
        lastIdx = targetIdx + 1;
        if (lastIdx >= pend.size())
            break;
    }


    if (hasStraggler)
    {
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }

    container = mainChain;
}

void PmergeMe::run(int argc, char** argv)
{
    // Chargement et validation des donnees d'entree.
    parseInput(argc, argv);

    std::cout << "Before: ";
    // Affichage de la sequence initiale.
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << "\n";
    std::cout << std::endl;

    struct timeval start;
    struct timeval end;

    // Mesure du tri sur vector.
    gettimeofday(&start, NULL);
    sortVector(_vec);
    gettimeofday(&end, NULL);
    double vecTime = getTimeInUs(start, end);

    // Mesure du tri sur deque.
    gettimeofday(&start, NULL);
    sortDeque(_deq);
    gettimeofday(&end, NULL);
    double deqTime = getTimeInUs(start, end);

    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << "\n";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
}
//insertion dichotomique
