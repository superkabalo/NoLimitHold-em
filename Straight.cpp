#include "Straight.h"

Straight::Straight(const Card& topCard)
{
	_topCard = topCard;
	_rank = 4;
}

int Straight::compareHands(const Hand& other)
{
	Card otherTopCard = dynamic_cast<const Straight&>(other).getTopCard();

	if (_topCard.rank > otherTopCard.rank)
	{
		return 1;
	}
	else if (_topCard.rank < otherTopCard.rank)
	{
		return 2;
	}
	return 0;
}

Card Straight::getTopCard() const
{
	return _topCard;
}
