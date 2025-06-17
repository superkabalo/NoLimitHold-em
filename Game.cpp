#include "Game.h"
const int playerColors[] = { 10, 2, 3, 4, 5, 6, 8, 9 };  // console colors of each player

void Game::initGame()
{
	changeColor(WHITE);  // make sure console color is white
	// initiate the game
	initBlinds();
	initPlayers();
	sbIndex = 0, bbIndex = 1;
}

void Game::startRound()
{
	initDeck();
	dealPlayerCards();

	takeBlinds();
	// if the game was over during any of the betting rounds this term would be false
	// in case this term is true that means that there is a showdown
	if (!(bettingRound(true) || flop() || turn() || river()))  // preflop round -> flop -> -> turn -> river
	{
		showdown();
	}

	kickPlayers();  // kick players without enough chips (or rebuy into the game)
	updatePlayerPositions();  // update blind positions
	roundCleanup();  // reset game variables
}

void Game::initPlayers()
{
	bool valid = false;
	int chips = 0;
	std::string name;

	while (!valid)
	{
		std::cout << "How many players will you be?" << std::endl;
		std::cin >> numPlayers;

		if (numPlayers > MAX_PLAYERS || numPlayers < MIN_PLAYERS)	// validate number of players
		{
			std::cout << "Number of players should be between 2 and 8!" << std::endl;
			continue;
		}
		valid = true;
	}

	remainingPlayers = numPlayers;  // set number of players remaining in the round

	for (int i = 0; i < numPlayers; i++)  // get starting number of chips
	{
		players.push_back(Player());  // add player
		// get player name
		std::cout << "Enter name of Player " << i + 1 << ": ";
		std::cin >> name;
		players[i].setName(name);

		std::cout << "Enter number of chips for " << players[i].getName() << ": ";
		std::cin >> chips;
		if (chips < bb)  // validate starting chips amount
		{
			std::cout << "Starting number of chips must be greater than or equal to the big blind!" << std::endl;
			i--;
			continue;
		}
		players[i].setChips(chips);   // set player chips

	}
	system("cls");
}

void Game::initBlinds()
{
	bool valid = false;

	while (!valid)
	{
		std::cout << "Enter Big Blind:" << std::endl;  // get big blind input
		std::cin >> bb;
		if (bb <= 0)
		{
			std::cout << "Big Blind must be bigger than 0!" << std::endl;
			continue;
		}
		valid = true;
	}

	valid = false;
	while (!valid)
	{
		std::cout << "Enter Small Blind:" << std::endl;  // get small blind input
		std::cin >> sb;
		if (sb <= 0 || sb > bb)
		{
			std::cout << "Small Blind must be bigger than 0 and not bigger than the Big Blind!" << std::endl;
			continue;
		}
		valid = true;
	}
	std::cout << std::endl;
}

void Game::initDeck()
{
	deck.initDeck();  // add all the cards to the deck
	deck.shuffleDeck();
}

void Game::dealPlayerCards()
{
	for (int i = 0; i < numPlayers; i++)  // deal first card to each player
	{
		players[i].setFirstCard(deck.dealCard());
	}

	for (int i = 0; i < numPlayers; i++)  // deal second card to each player
	{
		players[i].setSecondCard(deck.dealCard());
	}
}

void Game::roundCleanup()
{
	for (int i = 0; i < numPlayers; i++)
	{
		players[i].setChipsInPot(0);  // reset players chips in pot
	}
	communityCards.clear();	  // reset class members to their correct values for beginning a round
	potChips = 0;
	remainingPlayers = numPlayers;
	priceOfPoker = bb;
}

void Game::kickPlayers()
{
	char choice;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getChips() < bb)  // check if player doesn't have enough funds
		{
			std::cout << players[i].getName() << ", you don't have enough chips to pay for the Big Blind!" << std::endl
				<< "Would you like to rebuy into the game (Minimum of " << bb - players[i].getChips() << " Chips) or leave the game?" << std::endl
				<< "0 - Rebuy" << std::endl
				<< "Any other key - Leave the game" << std::endl;
			std::cin >> choice;
			if (choice == '0')  // player chose to rebuy into the game
			{
				rebuy(i);
			}
			else
			{
				numPlayers--;  // remove player from the game
				players.erase(players.begin() + i);
			}
			std::cout << std::endl;
		}
	}
	system("cls");
}

void Game::rebuy(const int index)
{
	int amount = 0;
	bool valid = false;
	std::cout << "How much chips would you like to add to your stack, the minimum is " << bb - players[index].getChips() << " Chips in order to match the Big Blind" << std::endl
		<< "It is recommended to buy in with at least 20 Big Blinds (" << bb * 20 << " Chips)" << std::endl;
	std::cin >> amount;

	if (amount < bb - players[index].getChips())  // insufficient rebuy
	{
		std::cout << "Insufficient amount! Goodbye " << players[index].getName() << std::endl << std::endl;
		numPlayers--;  // remove player from the game
		players.erase(players.begin() + index);
	}
	else
	{
		players[index].modifyChips(amount);  // add the chips to the player
	}
}

void Game::updatePlayerPositions()
{
	(sbIndex + 1 == numPlayers) ? sbIndex = 0 : sbIndex++;  // increment blinds indexes
	(bbIndex + 1 == numPlayers) ? bbIndex = 0 : bbIndex++;
}

void Game::takeBlinds()
{
	std::cout << players[sbIndex].getName() << " is the Small Blind (" << sb << " Chips)" << std::endl
		<< players[bbIndex].getName() << " is the Big Blind (" << bb << " Chips)" << std::endl << std::endl << std::endl;
	// take small blind and add it to the pot
	players[sbIndex].setChips(players[sbIndex].getChips() - sb);
	players[sbIndex].setChipsInPot(sb);
	potChips += sb;
	// take big blind and add it to the pot
	players[bbIndex].setChips(players[bbIndex].getChips() - bb);
	players[bbIndex].setChipsInPot(bb);
	potChips += bb;

	priceOfPoker = bb;  // update the price of poker
}

bool Game::flop()
{
	std::cout << "The flop is:" << std::endl;

	deck.dealCard();  // burn card
	communityCards.push_back(deck.dealCard());  // open 3 flop cards
	displayCard(communityCards.back());
	communityCards.push_back(deck.dealCard());
	displayCard(communityCards.back());
	communityCards.push_back(deck.dealCard());
	displayCard(communityCards.back());
	std::cout << std::endl;

	return bettingRound(false);
}

bool Game::turn()
{
	std::cout << "The turn is:" << std::endl;

	deck.dealCard();  // burn card
	communityCards.push_back(deck.dealCard());  // open 1 turn card
	displayCard(communityCards.back());
	std::cout << std::endl;

	return bettingRound(false);
}

bool Game::river()
{
	std::cout << "The river is:" << std::endl;

	deck.dealCard();  // burn card
	communityCards.push_back(deck.dealCard());  // open 1 river card
	displayCard(communityCards.back());
	std::cout << std::endl;

	return bettingRound(false);
}

bool Game::bettingRound(const bool preflopRound)
{
	char choice;
	int i = preflopRound ? bbIndex + 1 : sbIndex;   // i is the index of the first player to play
	int lastPlayerIndex = (i == 0) ? numPlayers : i;  // this discludes the actual last player because of the while loop stopping term structure
	minRaise = bb;

	do
	{
		if (i == numPlayers)  // 0 <= i < numPlayers (because i is an index
		{
			i -= numPlayers;
		}
		
		if (players[i].getChipsInPot() != FOLD)  // current player is in the game
		{
			changeColor(playerColors[i]);
			std::cout << "It is " << players[i].getName() << "'s turn:" << std::endl;
			players[i].printPlayerInfo();
		}
		else
		{
			i++;
			continue;  // skip over a player who folded
		}

		if (players[i].getChipsInPot() == priceOfPoker)  // current player has paid the price of poker
		{
			std::cout << "C - Check" << std::endl
				<< "R - Raise" << std::endl;
		}
		else  // current player has to call in order to play the round
		{
			std::cout << "C - Call (" << priceOfPoker - players[i].getChipsInPot() << " Chips)" << std::endl
				<< "R - Call and Raise" << std::endl;
		}
		std::cout << "F - Fold" << std::endl;  // player can fold at any point in the game

		std::cin >> choice;
		std::cout << std::endl;

		if (players[i].getChipsInPot() != priceOfPoker && choice == 'C')  // call
		{
			call(i);
		}
		else if (choice == 'R')
		{
			call(i);  // call before raising
			raise(i);
			lastPlayerIndex = (i == 0) ? numPlayers : i;  // change last player to the player before the raise
		}
		else if (choice == 'F')
		{
			fold(i);
			if (--remainingPlayers == 1)  // check if there is now only one player remaining
			{
				findWinningPlayer();  // find the remaining player and declare him the winner
				return true;  // no need for showdown, all players folded except one
			}
		}
		else if (choice != 'C')  // user didn't do any of the above and make sure it wasn't a check (check doesn't do anything)
		{
			std::cout << "Invalid choice!" << std::endl;
			i--;
		}
		i++;  // go to the next player
	} while (i != lastPlayerIndex);
	system("cls");
	changeColor(WHITE);
	return false;
}

void Game::fold(const int index)
{
	players[index].setChipsInPot(FOLD);  // player has folded
}

void Game::call(const int index)
{
	// move the required chips from the player to the pot
	potChips += priceOfPoker - players[index].getChipsInPot();
	players[index].modifyChips(-(priceOfPoker - players[index].getChipsInPot()));
	players[index].setChipsInPot(priceOfPoker);
}

void Game::raise(const int index)
{
	int raiseAmount = 0;
	bool valid = false;
	while (!valid)
	{
		std::cout << "Enter raise amount (Minimum " << minRaise << " Chips): ";
		std::cin >> raiseAmount;
		if (raiseAmount < minRaise || raiseAmount > players[index].getChips())  // check if the raise amount is valid
		{
			std::cout << "Raise amount must be at least the size of the minimum raise amount, and make sure you have enough chips!" << std::endl;
			continue;
		}
		std::cout << std::endl;
		valid = true;
	}
	minRaise = raiseAmount * 2;	 // double the minraise value
	priceOfPoker += raiseAmount;
	// take the raise chips from the player and add them to the pot
	potChips += raiseAmount;
	players[index].modifyChips(-raiseAmount);
	players[index].modiftChipsInPot(raiseAmount);
}

void Game::findWinningPlayer()
{
	for (int i = 0; i < numPlayers; i++)
	{
		if (players[i].getChipsInPot() != FOLD)  // find the only player who didn't fold
		{
			system("cls");
			changeColor(WHITE);
			winningPlayer(i);  // declare winning player
			break;
		}
	}
}

void Game::winningPlayer(const int index)
{
	players[index].modifyChips(potChips);  // give the winning player the chips
	std::cout << players[index].getName() << " has won and earned a pot of " << potChips << " Chips, he now has " << players[index].getChips() << " Chips in total" << std::endl;
	_getch();
	system("cls");
}

void Game::splitPot(std::vector<int> tiePlayers)
{
	std::cout << "The pot is split " << tiePlayers.size() << " ways!" << std::endl;
	for (int i = 0; i < tiePlayers.size(); i++)  // split the pot equally between all the tied players
	{
		players[i].modifyChips(potChips / tiePlayers.size());
		std::cout << players[i].getName() << " has tied and earned " << potChips / tiePlayers.size() << " Chips, he now has " << players[i].getChips() << " Chips" << std::endl;
	}
	_getch();
	system("cls");
}

void Game::showdown()
{
	Hand* bestHand = nullptr;
	Hand* curHand = nullptr;
	std::vector<Card> fullHand;
	int winningPlayerIndex = 0;
	std::vector<Hand> tieHands;
	std::vector<int> tiePlayers;
	bool tie = false;

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i].getChipsInPot() != FOLD)  // check if current player is in the game
		{
			fullHand = std::vector<Card>(communityCards.begin(), communityCards.end());  // create the current players full hand
			fullHand.push_back(players[i].getCards().first);
			fullHand.push_back(players[i].getCards().second);
			curHand = handDeterminator.determineHand(fullHand);  // determine hand rank

			if (bestHand == nullptr || curHand->getRank() > bestHand->getRank() ||  // check if current hand beats the current best one
				(curHand->getRank() == bestHand->getRank() && curHand->compareHands(*bestHand) == CUR_HAND_BETTER))
			{
				if (bestHand != nullptr)
				{
					delete bestHand;  // free dynamically allocated memory
				}
				// set new best hand and winning player
				bestHand = curHand;
				winningPlayerIndex = i;
				// define a new tie scenario in case a future hand ties with this one
				tiePlayers.clear();
				tiePlayers.push_back(i);
				tie = false;
			}
			else if (curHand->getRank() == bestHand->getRank() && curHand->compareHands(*bestHand) == TIE)  // hands are tied
			{
				delete curHand;  // free dynamically allocated memory
				// tie the current hand with the best current hadn
				tie = true;
				tiePlayers.push_back(i);
			}
			else  // cur hand is weaker
			{
				delete curHand;  // free dynamically allocated memory
			}
		}
	}
	if (tie)
	{
		splitPot(tiePlayers);  // split the pot in case of a tie
	}
	else
	{
		winningPlayer(winningPlayerIndex);  // declare the winning player
	}
	delete bestHand;  // free dynamically allocated memory
}

void Game::changeColor(const int desiredColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), desiredColor);
}
