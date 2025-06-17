#pragma once
#include "Hand.h"

class HighCard : public Hand
{
public:
	/// <summary>
	/// constructor - initiate the class fields
	/// </summary>
	/// <param name="highCard">vector of the high card + kicker</param>
	HighCard(const std::vector<Card>& highCard);
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) override;
	/// <summary>
	/// get the high card + kicker
	/// </summary>
	/// <returns>vector with the high card + kicker</returns>
	std::vector<Card> getHighCard() const;

private:
	std::vector<Card> _highCard;  // save the top 5 cards for comparison of high card hands (kicker)
};