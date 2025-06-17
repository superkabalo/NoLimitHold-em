#include "FourOfAKind.h"

FourOfAKind::FourOfAKind(const std::vector<Card>& fourOfAKindCard)
{
	_fourOfAKindCard = fourOfAKindCard;
	_rank = 7;
}

int FourOfAKind::compareHands(const Hand& other)
{
	return sequentialCardRankComparison(_fourOfAKindCard, dynamic_cast<const FourOfAKind&>(other).getFourOfAKindCard());	 // compare the four of a kind card and then the kicker
}

std::vector<Card> FourOfAKind::getFourOfAKindCard() const
{
	return _fourOfAKindCard;
}
