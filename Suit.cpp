// Define << and ++ for suits
#include "Suit.h"
using namespace std;

ostream &operator<<(ostream &os, const suits &s) {
    if (s == suits::clubs)
	os << "C";
    else if (s == suits::diamonds)
	os << "D";
    else if (s == suits::hearts)
	os << "H";
    else if (s == suits::spades)
	os << "S";
    else 
	os << "?";

    return os;
}

suits &operator++(suits &s) {
    // If suits is not undefined, add one
    if (s != suits::undefined)
	s = suits(static_cast<int>(s) + 1);

    return s;
}
