#pragma once
#include "Card.h"
#include <vector>
#include <algorithm>

#define FIRST_VECTOR_BIGGER 1
#define SECOND_VECTOR_BIGGER 2
#define VECTORS_EQUAL 0

class Hand
{
public:
	/// <summary>
	/// get the hand's rank
	/// </summary>
	/// <returns>the hand's rank</returns>
	int getRank() const;
	/// <summary>
	/// compare two hands of the same rank (this object and the parameter)
	/// </summary>
	/// <param name="other">the second hand in the comparison</param>
	/// <returns>0 if this object hand is stronger than secondHand, 1 if the other hand is stronger, 2 if they are equal (which means splitting the pot)</returns>
	virtual int compareHands(const Hand& other) = 0;

protected:
	int _rank;

	/// <summary>
	/// compare two vectors of cards by rank (in order of the cards)
	/// </summary>
	/// <param name="first">the first vector in the comparison</param>
	/// <param name="second">the second vector</param>
	/// <returns>1 - if the first vector is bigger, 2 - if the second vector is bigger, 0 - the vector are equal</returns>
	static int sequentialCardRankComparison(const std::vector<Card>& first, const std::vector<Card>& second);
};