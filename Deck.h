#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Card.h"

#define CARD_COUNT 52

class Deck
{
public:
	/// <summary>
	/// initiate deck of cards
	/// </summary>
	void initDeck();
	/// <summary>
	/// shuffle deck of cards
	/// </summary>
	void shuffleDeck();
	/// <summary>
	/// deal a card out of the back of the deck
	/// </summary>
	/// <returns>the dealt card</returns>
	Card dealCard();
private:
	std::vector<Card> _cards;
};
