// Define suits, clarify the << and ++ operator for suits
#ifndef _SUIT_
#define _SUIT_

#include <iostream>
using namespace std;

enum class suits {clubs, diamonds, hearts, spades, undefined};

ostream &operator<<(ostream &, const suits &);
suits &operator++(suits &);

#endif
