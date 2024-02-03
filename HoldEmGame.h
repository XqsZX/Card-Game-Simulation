/* Define the HoldEmState and HoldEmHandRank enum
 * Clarify the HoldEmGame class
 * Clarify the << and < operator
 */
#ifndef _HOLDEMGAME_
#define _HOLDEMGAME_

#include <vector>
#include <iostream>
#include <string>

#include "Game.h"
#include "Suit.h"
#include "HoldEm.h"

using namespace std;

enum class HoldEmState {preflop, flop, turn, river, undefined};
enum class HoldEmHandRank {xhigh, pair, twopair, threeofakind, straight, flush, fullhouse, fourofakind, straightflush, undefined};

class HoldEmGame : public Game {
private:
    // figure out the HoldEmHandRank the player have
    HoldEmHandRank holdem_hand_evaluation(const CardSet<HoldEmRank, suits>&);
protected:
    HoldEmState hes;
    HoldEmDeck hed;
    vector<CardSet<HoldEmRank, suits>> hands;
    // a board for the game
    CardSet<HoldEmRank, suits> commonBoard;
    virtual void deal();
    void print(ostream &, const size_t) const;
    void collectCards();
    string ask(ostream &, istream &);

public:
    HoldEmGame(int, const char *[]);
    virtual int play() override;

    // nested struct to show a player hand
    struct PlayerHand {
        CardSet<HoldEmRank, suits> hand;
        int playerName;
        HoldEmHandRank hehr;

        PlayerHand(const CardSet<HoldEmRank, suits>& hand, const int playerName, HoldEmHandRank hehr) : hand(hand), playerName(playerName), hehr(hehr) {}
    };
};

ostream& operator<<(ostream&, const HoldEmHandRank&);
bool operator<(const HoldEmGame::PlayerHand&, const HoldEmGame::PlayerHand&);

#endif
