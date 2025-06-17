#pragma once
#include "Hand.h"

class TwoPair : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="pairs">vector of the pairs + kicker</param>
	TwoPair(const std::vector<Card>& pairs);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the pairs + kicker
	/// </summary>
	/// <returns>vector of the pairs + kicker</returns>
	std::vector<Card> getPairs() const;
private:
	std::vector<Card> _pairs;  // pairs[0] = first pair card, pairs[1] = second pair card, pairs[2] = kicker card
};