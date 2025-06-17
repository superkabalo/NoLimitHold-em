#pragma once
#include "Hand.h"

class Straight : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="topCard">the top card of the straight</param>
	Straight(const Card& topCard);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the top card of the straight
	/// </summary>
	/// <returns>the top card of the straight</returns>
	Card getTopCard() const;

private:
	Card _topCard;
};