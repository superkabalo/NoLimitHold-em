#include "Deck.h"

void Deck::initDeck()
{
	Card cur;
	for (int i = 0; i < SUITE_COUNT; i++)  // insert all the cards to the deck
	{
		for (int j = 0; j < RANK_COUNT; j++)
		{
			cur = { (Suite)i, (Rank)j };
			_cards.push_back(cur);
		}
	}
}

void Deck::shuffleDeck()
{
	std::random_device rd;  // shuffle the deck (code from the internet)
	std::mt19937 g(rd());
	std::shuffle(_cards.begin(), _cards.end(), g);
}

Card Deck::dealCard()
{
	Card ret = _cards.back();
	_cards.pop_back();  // remove the dealt card from the deck
	return ret;
}