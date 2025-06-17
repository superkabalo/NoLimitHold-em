#include "ThreeOfAKind.h"

ThreeOfAKind::ThreeOfAKind(const std::vector<Card>& set)
{
	_set = set;
	_rank = 3;
}

int ThreeOfAKind::compareHands(const Hand& other)
{	
	return sequentialCardRankComparison(_set, dynamic_cast<const ThreeOfAKind&>(other).getSet());	 // compare the set and kickers card by card
}

std::vector<Card> ThreeOfAKind::getSet() const
{
	return _set;
}
