/* Define the PinochleRank
 * Clarify the PinochleDeck
 */
#ifndef _PINOCHLE_
#define _PINOCHLE_

#include <vector>
#include <iostream>

#include "Suit.h"
#include "Card_T.h"
#include "Deck.h"
#include "CardSet.h"

using namespace std;

enum class PinochleRank {Nine, Jack, Queen, King, Ten, Ace, Undefined};

ostream &operator<<(ostream &, const PinochleRank &);
PinochleRank &operator++(PinochleRank &);

class PinochleDeck : public Deck<PinochleRank, suits> {
public:
    PinochleDeck() {
	for (PinochleRank i = PinochleRank::Nine; i != PinochleRank::Undefined; ++i) {
	    for (suits j = suits::clubs; j != suits::undefined; ++j) {
		Card<PinochleRank, suits> card(i, j);
		cards.push_back(card); 
		cards.push_back(card);
	    }
	}
    }
};
#endif
