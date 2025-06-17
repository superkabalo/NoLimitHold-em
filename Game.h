#pragma once
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include "Deck.h"
#include "Player.h"
#include "Hand.h"
#include "HandDeterminator.h"

#define WHITE 7
#define MIN_PLAYERS 2
#define MAX_PLAYERS 8
#define FOLD -1
#define TIE 0
#define CUR_HAND_BETTER 1

class Game
{
public:
	/// <summary>
	/// initiate the game details (set blinds, player details)
	/// </summary>
	void initGame();
	/// <summary>
	/// start a round of poker
	/// </summary>
	void startRound();

private:
	// blinds and blind player indexes
	int sb;
	int bb;
	int sbIndex;
	int bbIndex;

	std::vector<Card> communityCards;
	Deck deck;
	HandDeterminator handDeterminator;

	// player related
	std::vector<Player> players;
	int numPlayers;

	// round related
	int remainingPlayers;  // remaining players in current round (who have not folded)
	int potChips;  // num of chips in pot
	int priceOfPoker;  // price to stay in the game (last raise/big blind)
	int minRaise;

	/// <summary>
	/// initiate the number of players in the game and their chips
	/// </summary>
	void initPlayers();
	/// <summary>
	/// initiate the blind sizes
	/// </summary>
	void initBlinds();
	/// <summary>
	/// initiate the deck of cards
	/// </summary>
	void initDeck();
	/// <summary>
	/// deal two cards to each player
	/// </summary>
	void dealPlayerCards();
	/// <summary>
	/// restore the class's values so that it is ready to start another round
	/// </summary>
	void roundCleanup();
	/// <summary>
	/// kick out of the game the players that don't have at least 1 big blind of chips
	/// </summary>
	void kickPlayers();
	/// <summary>
	/// if a player chose to rebuy into the game
	/// </summary>
	/// <param name="index">index of the players who chose to rebuy in</param>
	void rebuy(const int index);
	/// <summary>
	/// update the blind indexes
	/// </summary>
	void updatePlayerPositions();
	/// <summary>
	/// take the blinds from each player's stack
	/// </summary>
	void takeBlinds();
	/// <summary>
	/// open three cards and start a betting round
	/// </summary>
	/// <returns>wether the game was over during the flop (everyone folded)</returns>
	bool flop();
	/// <summary>
	/// open the turn card and start a betting round
	/// </summary>
	/// <returns>wether the game was over during the turn (everyone folded)</returns>
	bool turn();
	/// <summary>
	/// open the river card and start a betting round
	/// </summary>
	/// <returns>wether the game was over during the river (everyone folded)</returns>
	bool river();
	/// <summary>
	/// do a betting round (each player has the option to check, raise, fold... according to the game's rules)
	/// </summary>
	/// <param name="preflopRound">bool value of wether it is the first betting round (before the flop) or not</param>
	/// <returns>wether the game was over during the round (everyone folded)</returns>
	bool bettingRound(const bool preflopRound);
	/// <summary>
	/// player chose to fold
	/// </summary>
	/// <param name="index">index of the folding player</param>
	void fold(const int index);
	/// <summary>
	/// player chose to call
	/// </summary>
	/// <param name="index">index of the calling player</param>
	void call(const int index);
	/// <summary>
	/// player chose to raise
	/// </summary>
	/// <param name="index">index of the raising player</param>
	void raise(const int index);
	/// <summary>
	/// find the winning player in case there is only one player left in the game (everyone else folded)
	/// </summary>
	void findWinningPlayer();
	/// <summary>
	/// print out a message with the winning player and the winning details
	/// </summary>
	/// <param name="index">the index of the winning player</param>
	void winningPlayer(const int index);
	/// <summary>
	/// split the pot between the tied players
	/// </summary>
	/// <param name="tiePlayers">a vector with the indexes of the tied players</param>
	void splitPot(std::vector<int> tiePlayers);
	/// <summary>
	/// showdown of all the players remaining in the game after the betting is done (comparison of all the hands to find the winner)
	/// </summary>
	void showdown();
	/// <summary>
	/// change the color of the text in the console using the windows.h library
	/// </summary>
	/// <param name="desiredColor">the code of the desired color</param>
	static void changeColor(const int desiredColor);
};
