// Clarify the Card class and relavent functions
#ifndef _CARD_
#define _CARD_

#include <iostream>
using namespace std;

template<typename R, typename S>
struct Card {
    R Rank;
    S Suit;
    Card(const R &rank,const S &suit) : Rank(rank), Suit(suit) {};
};

template<typename R, typename S>
ostream &operator<<(ostream &, const Card<R, S> &);

// compare by rank
template<typename R, typename S>
bool lowerRank(const Card<R, S>&, const Card<R, S>&);

// compare by suit
template<typename R, typename S>
bool lowerSuit(const Card<R, S>&, const Card<R, S>&);

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Card_T.cpp"
#endif

#endif
