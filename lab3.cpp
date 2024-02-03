// Contain Main function
#include "Pinochle.h"
#include "PinochleGame.h"
#include "HoldEm.h"
#include "HoldEmGame.h"
#include "Uno.h"
#include "GoFishGame.h"
#include "Game.h"

#include <iostream>
#include <cstring>
#include <memory>

#define minArgc 2

using namespace std;

enum {Program, GameName, HoldEmLeastPlayers = 2, PinochlePlayers = 4, HoldEmMostPlayers = 9};
enum Result {SUCCESS, LACKINPUT, WRONGPLAYERNUM, CREATEGAMEFAILED, WRONGGAMENAME}; 
enum GoFish {GameDeck = 2, LeastPlayers = 2, MostPlayers = 5};

// Create a game based on command line arguments
shared_ptr<Game> create(int argc, const char *argv[]) {
    shared_ptr<Game> spg;
    try {
        if (strcmp(argv[GameName], "GoFish") == 0) {
            if (argc >= (GoFish::GameDeck + GoFish::LeastPlayers) && argc <= (GoFish::GameDeck + GoFish::MostPlayers)) {
                if (strcmp(argv[GoFish::GameDeck], "HoldEm") == 0) {
                    spg = make_shared<GoFishGame<suits, HoldEmRank, HoldEmDeck>>(argc - 1, argv + 1);
                } else if (strcmp(argv[GoFish::GameDeck], "Pinochle") == 0) {
                    spg =  make_shared<GoFishGame<suits, PinochleRank, PinochleDeck>>(argc - 1, argv + 1);
                } else if (strcmp(argv[GoFish::GameDeck], "Uno") == 0) {
                    spg =  make_shared<GoFishGame<Color, UnoRank, UnoDeck>>(argc - 1, argv + 1);
                } else {
                    cout << "GoFish Game's type of deck should be HoldEm, Pinochle or Uno!" << endl;
                }
            } else {
                cout << "Usage: ./filename GoFish player1 player2 ... (2 ~ 5 players) " << endl;
            }
        }
        else if (strcmp(argv[GameName], "Pinochle") == 0)
            spg = make_shared<PinochleGame>(argc, argv);
        else if (strcmp(argv[GameName], "HoldEm") == 0)
            spg = make_shared<HoldEmGame>(argc, argv);
    } catch (const std::exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
    return spg;
}

int main(int argc, const char *argv[]) {
    // usages for the program
    if (argc < minArgc) {
	cout << "Usage: ./filename game player1 player2 ..." << endl;
	return Result::LACKINPUT;
    }
    else if (strcmp(argv[GameName], "Pinochle") == 0 && argc != PinochlePlayers + minArgc) {
	cout << "Pinochle needs 4 players!" << endl;
	return Result::WRONGPLAYERNUM;
    }
    else if (strcmp(argv[GameName], "HoldEm") == 0 && (argc < (HoldEmLeastPlayers + minArgc) || argc > (HoldEmMostPlayers + minArgc))) {
	cout << "HoldEm needs 2 ~ 9 players!" << endl;
	return Result::WRONGPLAYERNUM;
    }
    else if (strcmp(argv[GameName], "Pinochle") != 0 && strcmp(argv[GameName], "HoldEm") != 0 && strcmp(argv[GameName], "GoFish") != 0) {
	cout << "The game name should be Pinochle, HoldEm or GoFish!" << endl;
	return Result::WRONGGAMENAME;
    }
    else {
	shared_ptr<Game> game = create(argc, argv);
	if (game)
	    game->play();
	else {
	    cout << "Create game failed" << endl;
	    return Result::CREATEGAMEFAILED;
        }
    }
    return Result::SUCCESS;
}
