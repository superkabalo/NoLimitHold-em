#include "Pair.h"

Pair::Pair(const std::vector<Card>& pair)
{
	_pair = pair;
	_rank = 1;
}

int Pair::compareHands(const Hand& other)
{
	return sequentialCardRankComparison(_pair, dynamic_cast<const Pair&>(other).getPair());	 // compare the pair and kickers card by card
}

std::vector<Card> Pair::getPair() const
{
	return _pair;
}
