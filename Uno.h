#ifndef UNO_H
#define UNO_H

#include "Deck.h"
#include "CardSet.h"

enum class Color {Red, Blue, Green, Yellow, Black, Undefined};

enum class UnoRank {Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Skip, Reverse, Drawtwo, Drawfour, Wild, Blank, Undefined};

ostream& operator<<(ostream& os, const UnoRank& rank);
UnoRank& operator++(UnoRank& rank);

ostream& operator<<(ostream& os, const Color& color);
Color& operator++(Color& color);

class UnoDeck : public Deck<UnoRank, Color> {
public:
    UnoDeck();
};

#endif
