// Clarification for Deck class and relavent functions
#ifndef _DECK_
#define _DECK_

#include <iostream>
#include <random>
#include <algorithm>

#include "CardSet.h"
using namespace std;

template <typename R, typename S>
class Deck : public CardSet<R, S> {
public:
    void shuffle();
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "Deck.cpp"
#endif

#endif
