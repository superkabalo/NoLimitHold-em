#pragma once
#include "Hand.h"

class Pair : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="pair">vector of the pair + kicker</param>
	Pair(const std::vector<Card>& pair);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the pair + kicker
	/// </summary>
	/// <returns>vector of the pair + kicker</returns>
	std::vector<Card> getPair() const;
private:
	std::vector<Card> _pair;  // pairs[0] = pair card, pairs[1] = first kicker card, pairs[2] = second kicker card, pairs[3] = third kicker card

};