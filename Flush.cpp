#include "Flush.h"

Flush::Flush(const std::vector<Card>& flushCards)
{
	_flushCards = flushCards;
	_rank = 5;
}

int Flush::compareHands(const Hand& other)
{
	return sequentialCardRankComparison(_flushCards, dynamic_cast<const Flush&>(other).getFlushCards());	 // compare the flush cards
}

std::vector<Card> Flush::getFlushCards() const
{
	return _flushCards;
}
