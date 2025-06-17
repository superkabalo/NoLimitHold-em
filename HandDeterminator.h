#pragma once
#include "Hand.h"
#include "RoyalFlush.h"
#include "StraightFlush.h"
#include "FourOfAKind.h"
#include "FullHouse.h"
#include "Flush.h"
#include "Straight.h"
#include "ThreeOfAKind.h"
#include "TwoPair.h"
#include "Pair.h"
#include "HighCard.h"

#define STRAIGHT_LENGTH 5
#define FOUR_OF_A_KIND_KICKER_COUNT 1
#define THREE_OF_A_KIND_KICKER_COUNT 2
#define MAX_KICKER_COUNT 5

class HandDeterminator
{
public:
	/// <summary>
	/// find the hand given the player's full hand cards
	/// </summary>
	/// <param name="fullHand">vector of the 5 community cards combined with the player's 2 hole cards</param>
	/// <returns>pointer to the player's hand</returns>
	Hand* determineHand(const std::vector<Card>& fullHand);

private:
	std::vector<Card> _fullHand;  // the 5 community cards combined with the player's 2 hole cards
	std::vector<int> _rankHashMap;
	std::vector<int> _suiteHashMap;
	Hand* _hand;  // the hand of the player
	
	/// <summary>
	/// check if the hand contains a royal flush or a straight flush and update the _hand field if it does
	/// </summary>
	/// <returns>true if a royal flush or straight flush is found, otherwise false</returns>
	bool checkRoyalStraightFlush();
	/// <summary>
	/// check if the hand contains a four of a kind and update the _hand field if it does
	/// </summary>
	/// <returns>true is a four of a kind is found, otherwise false</returns>
	bool checkFourOfAKind();
	/// <summary>
	/// check if the hand contains a full house and update the _hand field if it does
	/// </summary>
	/// <returns>true if a full house is found, otherwise false</returns>
	bool checkFullHouse();
	/// <summary>
	/// check if the hand contains a flush and update the _hand field if it does
	/// </summary>
	/// <returns>true if a flush is found, otherwise false</returns>
	bool checkFlush();
	/// <summary>
	/// check if the hand contains a straight and update the _hand field if it does
	/// </summary>
	/// <returns>true if a straight is found, otherwise false</returns>
	bool checkStraight();
	/// <summary>
	/// check if the hand contains a three of a kind and update the _hand field if it does
	/// </summary>
	/// <returns>true if a three of a kind is found, otherwise false</returns>
	bool checkThreeOfAKind();
	/// <summary>
	/// check if the hand contains a two pair, pair, or if none of them then find the high card, and update the _hand field accordingly
	/// </summary>
	/// <returns>true in any case, since there will always be at least a high card in the hand</returns>
	bool checkPairsHighCard();

	/// <summary>
	/// initiate the rank and suite hash maps according to the _fullHand
	/// </summary>
	void initHashMaps();
};
