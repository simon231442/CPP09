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
    //on va renvoyer en microsecondes, 1 secondes == 1'000'000 microsecondes
    return (end.tv_sec - start.tv_sec) * 1000000.0 + (end.tv_usec - start.tv_usec);
}

//cette fonction va remplir notre deq et vector
void PmergeMe::parseInput(int argc, char** argv)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.empty())
            throw std::invalid_argument("Error argv est vide");

        //on va se balader dans la string en verifiant chaque char
        for (size_t j = 0; j < arg.length(); ++j)
        {
            if (!std::isdigit(arg[j]))
                throw std::invalid_argument("Error");
        }
        long val = std::atol(arg.c_str());
        //on verifie si le nombre depasse les limites
        if (val <= 0 || val > 2147483647)
            throw std::invalid_argument("Error");
        _vec.push_back(static_cast<int>(val));
        _deq.push_back(static_cast<int>(val));
    }
}

//cette fonction va generer la suite de jacobstahl jusqu a une limite
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
    //cassage de recursion
    if (container.size() <= 1)
        return;

    //si on a pas un nombre de paires
    bool hasStraggler = (container.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler != 0)
    {
        //on prend le dernier nombre et on le supprime
        straggler = container.back();
        container.pop_back();
    }

    //on va creer nos paires
    //le plus grand nombre sera le premier elements de la paire
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (container[i] > container[i + 1])
            pairs.push_back(std::make_pair(container[i], container[i + 1]));
        else
            pairs.push_back(std::make_pair(container[i + 1], container[i]));
    }

    //-----------------------------------------------------------
    //  ici on va creer 2 vector 1 pour les plus grand et l autre pour les plus petit
    //  les 2 vector vont suivre la suite des plus grand qui seront dans l ordre
    //  c est pour ca qu on va premierement trier les plus grand
    //  et apres construire pend pour les plus petit
    //  en fonction des plus grand

    //on va sortir tout les plus grand dans un vector a part

    //vector pour les grands
    std::vector<int> mainChain;
    //vector pour les petits 
    std::vector<int> pend;

    //on sort les plus grands, comme ils sont les premiers
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);

    //appelle recursion sur les grand nombres
    //on va refaire ca tant qu il nous reste pas 1 seule paire
    sortVector(mainChain);

    //on va se balader dans les grands
    for (size_t i = 0; i < mainChain.size(); ++i)
    {
        //on va se balader dans les paires
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            //on va trouver la paire qui venait avec le grand
            if (mainChain[i] == pairs[j].first)
            {
                //on va push le petit dans pend
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
    //JACOB STYLE
    //
    //jacob style donne la limite ou de combien de comparaison on doit
    //faire pour rajouter des elements
    //donc en restant a cette limite    
    std::vector<size_t> jacob = generateJacobsthal(pend.size());
    size_t lastIdx = 1;
    //-----------------------------------------------------------

    //Jacob style = 0, 1, 1, 3, 5, 11, 21, 43, 85
    for (size_t i = 1; i < jacob.size(); ++i)
    {
        //on prend le nombre de jackobstyle
        //---------------------------------
        size_t targetIdx = jacob[i] - 1;
        if (targetIdx >= pend.size())
            targetIdx = pend.size() - 1;
        //---------------------------------

        //on ajoute les nombres en partant de l index de jackobstyle
        //-------------------------------------------------------------
        for (size_t j = targetIdx; j >= lastIdx; --j)
        {
            //va renvoyer l iterator du premier elements plus grand que pend[j]
            //comme mainChain sont dans l ordre ca sera le premier plus grand plus petit nombre
            //
            //c est dans lower bound qu on fait le binary search
            //
            //BINARY SEARCH :
            // 
            //on cherche qqc dans la chaine, on va prendre l elements du milieu on va le comparer a se qu on cherche
            //en fonction de si c est plus grand ou plus petit
            //on va enlever la moitier de droite ou de gauche
            std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), pend[j]);
            mainChain.insert(it, pend[j]);
            if (j == lastIdx)
                break;
        }
        //-------------------------------------------------------------

        //on prend l index commme ca on sait quand est ce qu on doit s arreter
        //--------------------------------
        lastIdx = targetIdx + 1;
        if (lastIdx >= pend.size())
            break;
        //--------------------------------
    }

    //si on a le nombre impair qui reste
    //on va l ajouter de la meme maniere que tout les autres
    if (hasStraggler)
    {
        std::vector<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }

    container = mainChain;
}

void PmergeMe::sortDeque(std::deque<int>& container)
{
    //cassage de recursion
    if (container.size() <= 1)
        return;

    //si on a un nombre impaire
    //------------------------------------------------
    bool hasStraggler = (container.size() % 2 != 0);
    int straggler = 0;
    if (hasStraggler) 
    {
        straggler = container.back();
        container.pop_back();
    }
    //------------------------------------------------

    //on creer les paires
    //----------------------------------------------------------------------
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < container.size(); i += 2)
    {
        if (container[i] > container[i + 1])
            pairs.push_back(std::make_pair(container[i], container[i + 1]));
        else
            pairs.push_back(std::make_pair(container[i + 1], container[i]));
    }
    //----------------------------------------------------------------------

    //on creer la mainChain des paires les plus grand
    //---------------------------------------------------------------
    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);
    //---------------------------------------------------------------

    //appelle recursiv
    sortDeque(mainChain);

    //creation deque des plus petit
    //----------------------------------------------------
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
    //----------------------------------------------------


    if (!pend.empty())
        mainChain.push_front(pend[0]);

    //creation des indexe jacbostyle
    std::vector<size_t> jacob = generateJacobsthal(pend.size());
    size_t lastIdx = 1;

    //boucle qui va tout coller ensemble
    //-----------------------------------------------------------------------------------------------
    for (size_t i = 1; i < jacob.size(); ++i)
    {
        //on met l index
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
    //-----------------------------------------------------------------------------------------------


    if (hasStraggler)
    {
        std::deque<int>::iterator it = std::lower_bound(mainChain.begin(), mainChain.end(), straggler);
        mainChain.insert(it, straggler);
    }

    container = mainChain;
}

void PmergeMe::run(int argc, char** argv)
{
    //on remplit notre classe
    parseInput(argc, argv);

    std::cout << "Before: ";
    //on ecrit les nombres de base
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << "\n";
    std::cout << std::endl;

    struct timeval start;
    struct timeval end;

    // Vector Sort
    //-------------------------------------------------------------------
    //on prend le temps start
    gettimeofday(&start, NULL);
    //on sort le vector
    sortVector(_vec);
    //on prend le temps end
    gettimeofday(&end, NULL);
    double vecTime = getTimeInUs(start, end);
    //-------------------------------------------------------------------

    // Deque Sort
    //
    //un deque sera plus long parceque ca memoire est fragmenter dans l ordinateur
    //-------------------------------------------------------------------
    gettimeofday(&start, NULL);
    sortDeque(_deq);
    gettimeofday(&end, NULL);
    double deqTime = getTimeInUs(start, end);
    //-------------------------------------------------------------------

    std::cout << "After:  ";
    for (size_t i = 0; i < _vec.size(); ++i)
        std::cout << _vec[i] << "\n";
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
}

