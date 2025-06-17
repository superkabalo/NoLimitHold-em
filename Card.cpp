#include "Card.h"

const std::string RankStr[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
const std::string SuiteStr[] = { "SPADES", "HEARTS", "DIAMONDS", "CLUBS" };

void displayCard(const Card& card)
{
	std::cout << RankStr[(int)card.rank] << " " << SuiteStr[(int)card.suite] << std::endl;  // print out the card's rank and suite
}
