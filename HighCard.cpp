#include "HighCard.h"

HighCard::HighCard(const std::vector<Card>& highCard)
{
	_rank = 0;
	_highCard = highCard;
}

int HighCard::compareHands(const Hand& other)
{	
	return sequentialCardRankComparison(_highCard, dynamic_cast<const HighCard&>(other).getHighCard());  // compare the hand card by card
}

std::vector<Card> HighCard::getHighCard() const
{
	return _highCard;
}
