// Define Game class and relavent functions
#include "Game.h"

const int startIndex = 2;

Game::Game(int argc, const char *argv[]) {
    // The index will start at 2
    for (int i = startIndex; i < argc; ++i)
	players.push_back(argv[i]); 
}
