// Clarify the Game class and relavent functions
#ifndef _GAME_
#define _GAME_

#include <string>
#include <vector>

using namespace std;

class Game {
protected:
    vector<string> players;

public:
    Game(int, const char *[]);
    // Pure virtual play member
    virtual int play() = 0;
};

#endif
