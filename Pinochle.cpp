#include "Pinochle.h"
using namespace std;

const int Pinochle_Rank_Error = 2;

ostream &operator<<(ostream &os, const PinochleRank &pr) {
    if (pr == PinochleRank::Nine)
	os << "9";
    else if (pr == PinochleRank::Jack)
	os << "J";
    else if (pr == PinochleRank::Queen)
	os << "Q";
    else if (pr == PinochleRank::King)
	os << "K";
    else if (pr == PinochleRank::Ten)
	os << "10";
    else if (pr == PinochleRank::Ace)
	os << "A";
    else
	os << "?";

    return os;
}

PinochleRank &operator++(PinochleRank &pr) {
    // If PinochleRank is not Undefined, add one
    if (pr != PinochleRank::Undefined) 
	pr = PinochleRank(static_cast<int>(pr) + 1);

    return pr;
}

