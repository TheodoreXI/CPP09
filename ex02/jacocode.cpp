#include <vector>
#include <algorithm>
#include <utility>

// ---- Jacobsthal sequence: 1, 1, 3, 5, 11, 21, 43, ... ----
std::vector<size_t> jacobsthalSequence(size_t m)
{
    std::vector<size_t> jacob;
    jacob.push_back(1);
    jacob.push_back(1);

    size_t idx = 1;
    while (jacob[idx] < m)
    {
        idx++;
        size_t next = jacob[idx - 1] + 2 * jacob[idx - 2];
        jacob.push_back(next);
    }
    return jacob;
}

// ---- Returns the insertion order (indices 2..P) following Jacobsthal ----
std::vector<size_t> insertionOrder(size_t P)
{
    std::vector<size_t> order;
    if (P < 2)
        return order;

    std::vector<size_t> jacob = jacobsthalSequence(P);
    size_t prev = 1;

    for (size_t i = 2; i < jacob.size(); i++)
    {
        size_t cur = std::min(jacob[i], P);
        for (size_t j = cur; j > prev; j--)
            order.push_back(j);
        prev = cur;
    }
    for (size_t j = prev + 1; j <= P; j++)   // safety: cover any leftover indices
        order.push_back(j);

    return order;
}

// ---- Binary insert `value` into main[begin, bound) ----
void binaryInsertBounded(std::vector<int> &main_, std::vector<int>::iterator bound, int value)
{
    std::vector<int>::iterator pos = std::lower_bound(main_.begin(), bound, value);
    main_.insert(pos, value);
}

// ---- Core recursive Ford-Johnson sort ----
std::vector<int> fordJohnson(std::vector<int> input)
{
    if (input.size() <= 1)
        return input;

    // STEP 1: pair up, bigger/smaller
    std::vector<std::pair<int, int> > pairs;
    bool hasLeftover = (input.size() % 2 != 0);
    int leftover = 0;

    size_t i = 0;
    for (; i + 1 < input.size(); i += 2)
    {
        int a = input[i];
        int b = input[i + 1];
        if (a < b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }
    if (hasLeftover)
        leftover = input[i];

    std::vector<int> winners;
    for (size_t k = 0; k < pairs.size(); k++)
        winners.push_back(pairs[k].first);

    // STEP 2: recurse on winners
    winners = fordJohnson(winners);

    // STEP 3a: seed main chain with winners[0] and its loser (free insert)
    std::vector<int> mainChain;
    mainChain.push_back(winners[0]);

    for (size_t j = 0; j < pairs.size(); j++)
    {
        if (pairs[j].first == winners[0])
        {
            mainChain.insert(mainChain.begin(), pairs[j].second);
            break;
        }
    }
    for (size_t k = 1; k < winners.size(); k++)
        mainChain.push_back(winners[k]);

    // STEP 3b: build pend list (losers for winners[1..P-1])
    std::vector<int> pend;
    for (size_t k = 1; k < winners.size(); k++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (pairs[j].first == winners[k])
            {
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }

    // STEP 3c: insert pend elements in Jacobsthal order
    std::vector<size_t> order = insertionOrder(winners.size());
    for (size_t o = 0; o < order.size(); o++)
    {
        size_t v = order[o];               // 1-based index of the winner (A)
        size_t pendIdx = v - 2;             // pend[0] belongs to winners[1], etc.
        int value = pend[pendIdx];
        int winnerValue = winners[v - 1];

        std::vector<int>::iterator bound = std::find(mainChain.begin(), mainChain.end(), winnerValue);
        binaryInsertBounded(mainChain, bound, value);
    }

    // STEP 3d: leftover, if any — search field is the whole chain
    if (hasLeftover)
        binaryInsertBounded(mainChain, mainChain.end(), leftover);

    return mainChain;
}

// ---- Wrapper matching your original signature ----
void PmergeMe::sorted(std::vector<int> &vect_cont)
{
    vect_cont = fordJohnson(vect_cont);
}