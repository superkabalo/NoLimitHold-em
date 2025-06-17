#include "Player.h"

void Player::setFirstCard(const Card& card)
{
	_cards.first = card;
}

void Player::setSecondCard(const Card& card)
{
	_cards.second = card;
}

std::pair<Card, Card> Player::getCards() const
{
	return _cards;
}

void Player::setChips(const int chips)
{
	_chips = chips;
}

void Player::modifyChips(const int chips)
{
	_chips += chips;
}

int Player::getChips() const
{
	return _chips;
}

void Player::setChipsInPot(const int chipsInPot)
{
	_chipsInPot = chipsInPot;
}

void Player::modiftChipsInPot(const int chipsInPot)
{
	_chipsInPot += chipsInPot;
}

int Player::getChipsInPot() const
{
	return _chipsInPot;
}

void Player::setName(const std::string& name)
{
	_name = name;
}

std::string Player::getName() const
{
	return _name;
}

void Player::printPlayerInfo() const
{
	// print players chips and cards
	std::cout << "Chips: " << _chips << std::endl;
	std::cout << "Cards:" << std::endl;
	displayCard(_cards.first);
	displayCard(_cards.second);
	std::cout << std::endl;
}
