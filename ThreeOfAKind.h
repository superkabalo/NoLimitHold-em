#pragma once
#include "Hand.h"

class ThreeOfAKind : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="set">vector of the set card + kicker</param>
	ThreeOfAKind(const std::vector<Card>& set);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the set card + kicker
	/// </summary>
	/// <returns>vector of the set card + kicker</returns>
	std::vector<Card> getSet() const;

private:
	std::vector<Card> _set;  // set[0] = set card, set[1] = first kicker card, set[2] = second kicker card
};