#include "FullHouse.h"

FullHouse::FullHouse(const std::vector<Card> setAndPair)
{
	_setAndPair = setAndPair;
	_rank = 6;
}

int FullHouse::compareHands(const Hand& other)
{
	return sequentialCardRankComparison(_setAndPair, dynamic_cast<const FullHouse&>(other).getSetAndPair());	 // compare the set and pair cards
}

std::vector<Card> FullHouse::getSetAndPair() const
{
	return _setAndPair;
}
