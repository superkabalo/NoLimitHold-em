#pragma once
#include "Card.h"
#include <iostream>


class Player
{
public:
	/// <summary>
	/// set first card of the hand
	/// </summary>
	/// <param name="card">first card of the hand</param>
	void setFirstCard(const Card& card);
	/// <summary>
	/// set second card of the hand
	/// </summary>
	/// <param name="card">the second card of the hand</param>
	void setSecondCard(const Card& card);
	/// <summary>
	/// get the player's cards
	/// </summary>
	/// <returns>a pair of the player's two cards</returns>
	std::pair<Card, Card> getCards() const;

	/// <summary>
	/// set amount of chips the player has
	/// </summary>
	/// <param name="chips">new amount of chips</param>
	void setChips(const int chips);
	/// <summary>
	/// modify amount of chips the player has
	/// </summary>
	/// <param name="chips">amount to modify the chips by (+)</param>
	void modifyChips(const int chips);
	/// <summary>
	/// get the player's chips
	/// </summary>
	/// <returns>amount of chips the player has</returns>
	int getChips() const;

	/// <summary>
	/// set amount of chips a player has in the pot
	/// </summary>
	/// <param name="chipsInPot">updated amount of chips the player has in the pot</param>
	void setChipsInPot(const int chipsInPot);
	/// <summary>
	/// modify amount of chips a player has
	/// </summary>
	/// <param name="chipsInPot">amount to modify the chips in pot value by (+)</param>
	void modiftChipsInPot(const int chipsInPot);
	/// <summary>
	/// get the amount of chips the player has in the pot
	/// </summary>
	/// <returns>amount of chips the player has in the pot</returns>
	int getChipsInPot() const;

	/// <summary>
	/// set the player's name
	/// </summary>
	/// <param name="name">the name of the player</param>
	void setName(const std::string& name);
	/// <summary>
	/// get the player name
	/// </summary>
	/// <returns>the player's name</returns>
	std::string getName() const;

	/// <summary>
	/// print out the player's info
	/// </summary>
	void printPlayerInfo() const;

private:
	std::string _name;
	std::pair<Card, Card> _cards;
	int _chips;
	int _chipsInPot;
};