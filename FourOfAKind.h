#pragma once
#include "Hand.h"

class FourOfAKind : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="fourOfAKindCard">the four of a king card + kicker</param>
	FourOfAKind(const std::vector<Card>& fourOfAKindCard);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the four of a kind card + kicker
	/// </summary>
	/// <returns>the four of a kind card with its kicker</returns>
	std::vector<Card> getFourOfAKindCard() const;

private:
	std::vector<Card> _fourOfAKindCard;  // _fourOfAKindCard[0] = the four of a kind card, _fourOfAKindCard[1] = kicker
};