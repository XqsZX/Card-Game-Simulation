#ifndef GO_FISH_GAME_H
#define GO_FISH_GAME_H

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <type_traits>

#include "Suit.h"
#include "HoldEm.h"
#include "Pinochle.h"
#include "Uno.h"
#include "CardSet.h"
#include "Game.h"

using namespace std;

template <typename S = suits, typename R = HoldEmRank, typename D = HoldEmDeck>
class GoFishGame : public Game {
public:
    GoFishGame(int argc, const char* argv[]);
    virtual ~GoFishGame()=default;

    virtual int play();
    // checks if there is a 4-of-a-kind in that player's hand
    bool collect_books(size_t);
    bool turn(size_t);

protected:
    D Deck;
    int GameID;
    map<int, string> outPlayer;
    vector<CardSet<R, S>> hands;
    vector<CardSet<R, S>> books;
    vector<int> booksNum;

    virtual void deal();

private:
    static_assert(std::is_base_of<CardSet<R, S>, D>::value, "DeckType must be derived from CardSet<RankType, SuitType>");
};

#include "GoFishGame.cpp"

#endif // GO_FISH_GAME_H

