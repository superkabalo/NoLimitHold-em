#include "Hand.h"

int Hand::getRank() const
{
    return _rank;
}

int Hand::sequentialCardRankComparison(const std::vector<Card>& first, const std::vector<Card>& second)
{
    for (int i = 0; i < first.size(); i++)
    {
        if (first[i].rank > second[i].rank)	// first hand is better
        {
            return FIRST_VECTOR_BIGGER;
        }
        else if (first[i].rank < second[i].rank)	// second hand is better
        {
            return SECOND_VECTOR_BIGGER;
        }
    }
    return VECTORS_EQUAL;	// tie (split the pot)
}