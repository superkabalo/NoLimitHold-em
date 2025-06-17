#pragma once
#include "Hand.h"

class FullHouse : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="setAndPair">vector of the set card and the pair card</param>
	FullHouse(const std::vector<Card> setAndPair);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the set card and pair card
	/// </summary>
	/// <returns>the set and pair card</returns>
	std::vector<Card> getSetAndPair() const;

private:
	std::vector<Card> _setAndPair;  // _setAndPair[0] = set card, _setAndPair[1] = pair card  
};