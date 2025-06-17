#include <iostream>
#include <conio.h>
#include "Game.h"


#include "Hand.h"
#include "HandDeterminator.h"


int main()
{
	int numPlayers = 0;
	char keepPlaying;
	Game game = Game();

	std::cout << "Greetings! Are you new here?" << std::endl
		<< "Press any key to start!" << std::endl;
	_getch();
	std::cout << std::endl;

	game.initGame();	// init game

	do
	{
		game.startRound();  // start round

		std::cout << "Would you like to play another round?" << std::endl;
		std::cout << "0 - No" << std::endl;
		std::cout << "Any other key - Yes" << std::endl;
		std::cin >> keepPlaying;
		system("cls");
	} while (keepPlaying != '0');

	std::cout << "Goodbye!" << std::endl;
	
	return 0;
}