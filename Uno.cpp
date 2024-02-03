#include "Uno.h"
static const int BLACK_NUM = 4;

std::ostream& operator<<(std::ostream& os, const Color& color) {
    switch (color) {
        case Color::Red: 
            os << "Red"; 
            break;
        case Color::Blue: 
            os << "Blue"; 
            break;
        case Color::Green: 
            os << "Green"; 
            break;
        case Color::Yellow: 
            os << "Yellow";
            break;
        case Color::Black:
            os << "Black";
            break;
        default:
            os << "Undefined";
            break;
    }
    return os;
}

Color& operator++(Color& color) {
    // Return undefined if color is undefined
    if (color == Color::Undefined) return color;
    // Otherwise plus one
    color = static_cast<Color>(static_cast<int>(color) + 1);
    return color;
}

std::ostream& operator<<(std::ostream& os, const UnoRank& rank) {
    switch (rank) {
        case UnoRank::Zero: 
            os << "Zero"; 
            break;
        case UnoRank::One:
            os << "One";
            break;
        case UnoRank::Two:
            os << "Two";
            break;
        case UnoRank::Three:
            os << "Three";
            break;
        case UnoRank::Four:
            os << "Four";
            break;
        case UnoRank::Five:
            os << "Five";
            break;
        case UnoRank::Six:
            os << "Six";
            break;
        case UnoRank::Seven:
            os << "Seven";
            break;
        case UnoRank::Eight:
            os << "Eight";
            break;
        case UnoRank::Nine:
            os << "Nine";
            break;
        case UnoRank::Skip:
            os << "Skip";
            break;
        case UnoRank::Reverse:
            os << "Reverse";
            break;
        case UnoRank::Drawtwo:
            os << "DrawTwo";
            break;
        case UnoRank::Drawfour:
            os << "DrawFour";
            break;
        case UnoRank::Wild:
            os << "Wild";
            break;
        case UnoRank::Blank:
            os << "Blank";
            break;
        default:
            os << "Undefined";
            break;
    }
    return os;
}

UnoRank& operator++(UnoRank& rank) {
    // Return undefined if rank is undefined 
    if (rank == UnoRank::Undefined) return rank;
    // Otherwise plus one
    rank = static_cast<UnoRank>(static_cast<int>(rank) + 1);
    return rank;
}

UnoDeck::UnoDeck() {
    // one red, one blue, one green, and one yellow card of rank zero
    for (Color color = Color::Red; color != Color::Black; ++color)
        this->cards.push_back(Card<UnoRank, Color>(UnoRank::Zero, color));
    // two red, two blue, two green, and two yellow cards of each rank one through drawtwo
    for (UnoRank rank = UnoRank::One; rank != UnoRank::Drawfour; ++rank) {
        for (Color color = Color::Red; color != Color::Black; ++color) {
            this->cards.push_back(Card<UnoRank, Color>(rank, color));
            this->cards.push_back(Card<UnoRank, Color>(rank, color));
        }
    }

    // four black cards of each rank drawfour through blank
    for (UnoRank rank = UnoRank::Drawfour; rank != UnoRank::Undefined; ++rank) 
        for (int i = 0; i < BLACK_NUM; ++i)
            this->cards.push_back(Card<UnoRank, Color>(rank, Color::Black));
}
