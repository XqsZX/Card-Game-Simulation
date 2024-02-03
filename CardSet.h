// Clarify the CardSet class and relavent functions
#ifndef _CARDSET_
#define _CARDSET_

#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>
#include <functional>

#include "Card_T.h"

using namespace std;

// Base class for Deck
template <typename R, typename S>
class CardSet {
protected:
    // Use a vector to store all cards
    vector<Card<R, S>> cards;

public:
    // Type Specifier
    typedef Card<R, S> card_type;
    typedef R rank_type;
    typedef S suit_type;
    typedef typename vector<Card<R, S>>::iterator card_iter;

    // Default Constructor
    CardSet() = default;
    // Copy Constructor
    CardSet(const CardSet<R, S>&);
    // Print out all cards with s cards per row
    void print(ostream &, size_t) const;
    // Push last card to another cardset
    CardSet<R, S> &operator>>(CardSet<R, S> &);
    // Find out if there are cards left
    bool isEmpty();
    // Static function
    // static vector<Card<R, S>> CardSet::*getCards();
    // Begin and End iterator
    card_iter begin() {
        return CardSet<R, S>::cards.begin();
    }

    card_iter end() {
        return CardSet<R, S>::cards.end();
    }

    void sort();

    // Move cards from another CardSet into this one
    void collect(CardSet<R, S> &);

    // Collect cards which match certain criteria
    void collect_if(CardSet<R, S> &, function<bool(Card<R, S>&)>);

    // Find a card matching the provided rank
    bool request(CardSet<R, S> &, R);
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "CardSet.cpp"
#endif

#endif
