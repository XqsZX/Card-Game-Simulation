/* Define HoldEmRank
 * Clarify HoldEmDeck class
 */
#ifndef _HOLDEM_
#define _HOLDEM_

#include <vector>
#include <iostream>

#include "Deck.h"
#include "Card_T.h"
#include "Suit.h"

using namespace std;

enum class HoldEmRank {Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace, Undefined};

ostream &operator<<(ostream &, const HoldEmRank &);
HoldEmRank &operator++(HoldEmRank &);

class HoldEmDeck : public Deck<HoldEmRank, suits> {
public:
    HoldEmDeck() {
	for (HoldEmRank i = HoldEmRank::Two; i != HoldEmRank::Undefined; ++i) {
	    for (suits j = suits::clubs; j != suits::undefined; ++j) {
		Card<HoldEmRank, suits> card(i, j);
		cards.push_back(card);
	    }
	}	
    }
};

#endif
