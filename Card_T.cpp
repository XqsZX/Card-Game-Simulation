// Definition for Card class
#include <iostream>
using namespace std;

template<typename R, typename S>
ostream &operator<<(ostream &os, const Card<R, S> &card) {
    os << card.Rank << card.Suit;
    return os;
}

// compare by rank
template<typename R, typename S>
bool lowerRank(const Card<R, S> &card1, const Card<R, S> &card2) {
    if (card1.Rank == card2.Rank)
	return card1.Suit < card2.Suit;
    else
	return card1.Rank < card2.Rank;
}

// compare by suit
template<typename R, typename S>
bool lowerSuit(const Card<R, S> &card1, const Card<R, S> &card2) {
    if (card1.Suit == card2.Suit)
	return card1.Rank < card2.Rank;
    else 
	return card1.Suit < card2.Suit;
}
