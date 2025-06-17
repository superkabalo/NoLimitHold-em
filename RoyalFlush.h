#pragma once
#include "Hand.h"

class RoyalFlush : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields (only the _rank in this case)
	/// </summary>
	RoyalFlush();
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;

private:
};