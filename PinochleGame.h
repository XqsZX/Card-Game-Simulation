/* Define the PinochleMelds
 * Clarify the PinochleGame class and relavent functions
 */
#ifndef _PINOCHLEGAME_
#define _PINOCHLEGAME_

#include <vector>
#include <iostream>
#include <string>

#include "Game.h"
#include "Suit.h"
#include "Pinochle.h"
#include "CardSet.h"

using namespace std;

enum class PinochleMelds {dix, offsuitmarriage, fortyjacks, pinochle, insuitmarriage, sixtyqueens, eightykings, hundredaces, insuitrun, doublepinochle, fourhundredjacks, sixhundredqueens, eighthundredkings, thousandaces, insuitdoublerun};

class PinochleGame : public Game {
private:
    void suit_independent_evaluation(const CardSet<PinochleRank, suits> &, vector<PinochleMelds> &);
protected:
    PinochleDeck pd;
    // Store the hands of the players in the game
    vector<CardSet<PinochleRank, suits>> hands;
    virtual void deal();
    void print(ostream &, const size_t);
    void collectCards();
    // Ask for stop
    string ask(ostream &, istream &);

public:
    PinochleGame(int, const char *[]);
    virtual int play() override;
    static const vector<unsigned int> values_PinochleMelds;
};

ostream& operator<<(ostream &, const PinochleMelds &);

#endif
