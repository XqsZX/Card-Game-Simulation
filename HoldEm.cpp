// Define << and ++ for HoldEmRank
#include "HoldEm.h"

using namespace std;

ostream &operator<<(ostream &os,const HoldEmRank &he) {
    if (he == HoldEmRank::Two)
	os << "2";
    else if (he == HoldEmRank::Three)
	os << "3";
    else if (he == HoldEmRank::Four)
	os << "4";
    else if (he == HoldEmRank::Five)
	os << "5";
    else if (he == HoldEmRank::Six)
	os << "6";
    else if (he == HoldEmRank::Seven)
	os << "7";
    else if (he == HoldEmRank::Eight)
	os << "8";
    else if (he == HoldEmRank::Nine)
	os << "9";
    else if (he == HoldEmRank::Ten)
	os << "10";
    else if (he == HoldEmRank::Jack)
	os << "J";
    else if (he == HoldEmRank::Queen)
	os << "Q";
    else if (he == HoldEmRank::King)
	os << "K";
    else if (he == HoldEmRank::Ace)
	os << "A";
    else
	os << "?";

    return os;
}

HoldEmRank &operator++(HoldEmRank &he) {
    // If he is not Undefined, change it to be the next one
    if (he != HoldEmRank::Undefined)
	he = HoldEmRank(static_cast<int>(he) + 1);

    return he;
}
