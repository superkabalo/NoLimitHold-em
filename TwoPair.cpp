#include "TwoPair.h"

TwoPair::TwoPair(const std::vector<Card>& pairs)
{
	_pairs = pairs;
	_rank = 2;
}

int TwoPair::compareHands(const Hand& other)
{
	return sequentialCardRankComparison(_pairs, dynamic_cast<const TwoPair&>(other).getPairs());	 // compare the pairs and kicker card by card
}

std::vector<Card> TwoPair::getPairs() const
{
	return _pairs;
}
