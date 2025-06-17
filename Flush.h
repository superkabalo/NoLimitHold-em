#pragma once
#include "Hand.h"

class Flush : public Hand
{
public:
	/// <summary>
	/// constructor - initiate class fields
	/// </summary>
	/// <param name="flushCards">the cards constructing the flush</param>
	Flush(const std::vector<Card>& flushCards);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the flush cards
	/// </summary>
	/// <returns>the flush cards</returns>
	std::vector<Card> getFlushCards() const;

private:
	std::vector<Card> _flushCards;  // save the 5 flush cards for hand comparison
};