#include "StraightFlush.h"

StraightFlush::StraightFlush(const Card& topCard)
{
	_topCard = topCard;
	_rank = 8;
}

int StraightFlush::compareHands(const Hand& other)
{
	Card otherTopCard = dynamic_cast<const StraightFlush&>(other).getTopCard();

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

Card StraightFlush::getTopCard() const
{
	return _topCard;
}
