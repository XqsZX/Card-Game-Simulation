// Define the functions for HoldEmGame
#include "HoldEmGame.h"
#include <map>
#define startIndex 2
#define flopCards 3
#define preflopCards 2
#define boardWidth 5
#define SUCCESS 0
#define STD_NUM 5
#define PAIR 2
#define HoldEm_rank_size 14
#define HoldEm_suit_size 5

HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), hes(HoldEmState::preflop) {
    for(int i = startIndex; i < argc; ++i) {
	CardSet<HoldEmRank, suits> cs;
	hands.push_back(cs);
    }
}

void HoldEmGame::deal() {
    switch (hes) {
	case HoldEmState::preflop:
	    for (size_t i = 0; i < preflopCards; ++i) {
		for (auto it = hands.begin(); it != hands.end(); ++it)
		    hed >> *it;
	    }
	    hes = HoldEmState::flop;
	    break;
	case HoldEmState::flop:
	    for (size_t i = 0; i < flopCards; ++i)
		hed >> commonBoard;
	    hes = HoldEmState::turn;
	    break;
	case HoldEmState::turn:
	    hed >> commonBoard;
	    hes = HoldEmState::river;
	    break;
	case HoldEmState::river:
	    hed >> commonBoard;
	    hes = HoldEmState::undefined;
	    break;
	default:
	    break;
    }
}

void HoldEmGame::print(ostream& os, const size_t len) const {
    for (size_t i = 0; i < players.size(); ++i) {
	os << "Player: " << players[i] << endl;
	hands[i].print(os, len);
    }
}

void HoldEmGame::collectCards() {
    for (auto it = hands.begin(); it != hands.end(); ++it)
	hed.collect(*it);
    
    // Collect cards from the board
    hed.collect(commonBoard);
}

string HoldEmGame::ask(ostream& os, istream& is) {
    // ask for continue
    os << "Want to end this Game? (yes or no): " << endl;
    string answer;
    is >> answer;

    return answer;  
}

ostream& operator<<(ostream& os, const HoldEmHandRank& hehr) {
    switch (hehr) {
        case HoldEmHandRank::xhigh:
            os << "xhigh";
            break;
        case HoldEmHandRank::pair:
            os << "pair";
            break;
        case HoldEmHandRank::twopair:
            os << "twopair";
            break;
        case HoldEmHandRank::threeofakind:
            os << "threeofakind";
            break;
        case HoldEmHandRank::straight:
            os << "straight";
            break;
        case HoldEmHandRank::flush:
            os << "flush";
            break;
        case HoldEmHandRank::fullhouse:
            os << "fullhouse";
            break;
        case HoldEmHandRank::fourofakind:
            os << "fourofakind";
            break;
        case HoldEmHandRank::straightflush:
            os << "straightflush";
            break; 
	case HoldEmHandRank::undefined:
	    os << "undefined";
	    break;
    }
    return os;
}

int HoldEmGame::play() {
    cout << "HoldEm begin" << endl;
    
    while (true) {
	// call the deck's shuffle member function
	hed.shuffle();
	// set the HoldEmState to be preflop
	hes = HoldEmState::preflop;
	// deal two cards to each player's hand
	deal();
	// print out player's name and the cards
	print(cout, preflopCards);
	// deal three cards to the board member variable
	deal();
	// print out "BOARD (flop)" and then the cards in the board member variable
	cout << "BOARD (flop):" << endl;
	commonBoard.print(cout, boardWidth);
    vector<HoldEmGame::PlayerHand> hegph;
    for (size_t i = 0; i < players.size(); ++i)
        hegph.emplace_back(hands[i], i, HoldEmHandRank::undefined);

    for (size_t j = 0; j < hegph.size(); ++j) {
        CardSet<HoldEmRank, suits> tmp(commonBoard);
        while (!tmp.isEmpty())
            tmp >> hegph[j].hand;

        hegph[j].hehr = holdem_hand_evaluation(hegph[j].hand);
    }

    sort(hegph.begin(), hegph.end());
    reverse(hegph.begin(), hegph.end());

    for (const auto& ph : hegph) {
        cout << "Player" << ph.playerName << ": ";
        ph.hand.print(cout, boardWidth);
        cout << "Hand Rank for now: " << ph.hehr << endl;
    }

	// deal the fourth card to the board member variable
	deal();
	// print out "BOARD (turn)" and then the cards in the board member variable
	cout << "BOARD (turn):" << endl;
	commonBoard.print(cout, boardWidth);
	// deal the fifth and final card to the board member variable
	deal();
	// print out "BOARD (river)" and then the cards in the board member variable
	cout << "BOARD (river):" << endl;
	commonBoard.print(cout, boardWidth);
	// move the cards back out of each player's hand into the deck
	collectCards();
	// asks the user whether or not to end the game
	if (ask(cout, cin) == "yes")
	// read in a string - if "yes" return a value to indicate success
	    return SUCCESS;
    }
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<HoldEmRank, suits>& cs) {
    CardSet<HoldEmRank, suits> cs0(cs);
    vector<Card<HoldEmRank, suits>> vc(cs0.begin(), cs0.end());

    // STD_NUM is 5
    if (vc.size() != STD_NUM)
        return HoldEmHandRank::undefined;

    // sort in ascending order
    sort(vc.begin(), vc.end(), lowerRank<HoldEmRank, suits>);
    reverse(vc.begin(), vc.end());

    // flag for flush
    bool isFlush = true;
    // flag for straight
    bool isStraight = true;
    suits s = vc[0].Suit;
    HoldEmRank r = vc[0].Rank;

    map<HoldEmRank, int> rankCount;
    ++rankCount[vc[0].Rank];

    for (size_t i = 1; i < STD_NUM; ++i) {
        if (vc[i].Suit != s) isFlush = false;
        if (static_cast<int>(vc[i].Rank) != static_cast<int>(r) + 1) isStraight = false;
        ++rankCount[vc[i].Rank];
    }

    if (isFlush && (isStraight || (vc[0].Rank == HoldEmRank::Ace && vc[1].Rank == HoldEmRank::Ten))) {
        return HoldEmHandRank::straightflush;
    }

    for (auto& p : rankCount) {
        if (p.second == 4) 
            return HoldEmHandRank::fourofakind;
    }

    // flag for three
    bool isThree = false;
    // flag for two
    bool isTwo = false;

    for (auto& p : rankCount) {
        if (p.second == 3) isThree = true;
        else if (p.second == 2) isTwo = true;
    }

    if (isThree && isTwo)
        return HoldEmHandRank::fullhouse;
    if (isFlush)
        return HoldEmHandRank::flush;
    if (isStraight)
        return HoldEmHandRank::straight;
    if (isThree)
        return HoldEmHandRank::threeofakind;

    // flag for pairs
    int pairs = 0;
    for (auto& p : rankCount)
        if (p.second == 2)
            ++pairs;

    if (pairs == 2)
        return HoldEmHandRank::twopair;
    if (pairs == 1)
        return HoldEmHandRank::pair;

    return HoldEmHandRank::xhigh;
}

// function to compare HoldEmRank
bool compareHoldEmRank(const HoldEmRank& her1, const HoldEmRank& her2) {
    return static_cast<int>(her1) > static_cast<int>(her2);
}

bool operator<(const HoldEmGame::PlayerHand& ph1, const HoldEmGame::PlayerHand& ph2) {
    // If HoldEmHandRank is diffrent, judge by it
    if (ph1.hehr != ph2.hehr)
        return ph1.hehr < ph2.hehr;

    CardSet<HoldEmRank, suits> ph1Copy(ph1.hand);
    CardSet<HoldEmRank, suits> ph2Copy(ph2.hand);
    vector<Card<HoldEmRank, suits>> ph1Cards(ph1Copy.begin(), ph1Copy.end());
    vector<Card<HoldEmRank, suits>> ph2Cards(ph2Copy.begin(), ph2Copy.end());

    // two maps for rank count
    map<HoldEmRank, int> rankCount1;
    map<HoldEmRank, int> rankCount2;

    for (size_t i = 0; i < STD_NUM; ++i) {
        ++rankCount1[ph1Cards[i].Rank];
        ++rankCount2[ph2Cards[i].Rank];
    }

    switch (ph1.hehr) {
        case HoldEmHandRank::pair:
        case HoldEmHandRank::twopair: {
	    // vectors for pair and non-pair
            vector<HoldEmRank> pair1, pair2;
            vector<HoldEmRank> nonpair1, nonpair2;
            
            for (const auto& rc1 : rankCount1) {
                if (rc1.second == 2)
                    pair1.push_back(rc1.first);
                else if (rc1.second == 1)
                    nonpair1.push_back(rc1.first);
            }
            for (const auto& rc2 : rankCount2) {
                if (rc2.second == 2)
                    pair2.push_back(rc2.first);
                else if (rc2.second == 1)
                    nonpair2.push_back(rc2.first);
            }

	    // sort in ascending order
            sort(pair1.begin(), pair1.end(), compareHoldEmRank);
            sort(pair2.begin(), pair2.end(), compareHoldEmRank);
            sort(nonpair1.begin(), nonpair1.end(), compareHoldEmRank);
            sort(nonpair2.begin(), nonpair2.end(), compareHoldEmRank);

            for (size_t i = 0; i < pair1.size(); ++i)
                if (pair1[i] != pair2[i])
                    return pair1[i] < pair2[i];

            for (size_t j = 0; j < nonpair1.size(); ++j)
                if (nonpair1[j] != nonpair2[j])
                    return nonpair1[j] < nonpair2[j];
            break;
	}

        case HoldEmHandRank::threeofakind:
        case HoldEmHandRank::fullhouse: {
	    // Store the rank of three
            HoldEmRank Three1, Three2;

            for (const auto& rc1 : rankCount1) 
                if (rc1.second == 3)
                    Three1 = rc1.first;

            for (const auto& rc2 : rankCount2)
                if (rc2.second == 3)
                    Three2 = rc2.first;

            if (Three1 != Three2)
                return Three1 < Three2;
            break;
	}

        case HoldEmHandRank::straight:
        case HoldEmHandRank::straightflush: {
	    // store the highest rank
            vector<HoldEmRank> straight1, straight2;
            for (const auto& rc1 : rankCount1)
                straight1.push_back(rc1.first);
            for (const auto& rc2 : rankCount2)
                straight2.push_back(rc2.first);

            sort(straight1.begin(), straight1.end(), compareHoldEmRank);
            sort(straight2.begin(), straight2.end(), compareHoldEmRank);

            if (straight1[0] != straight2[0])
                return straight1[0] < straight2[0];
            break;
	}

        case HoldEmHandRank::flush:
        case HoldEmHandRank::xhigh: {
	    // store the rank of all cards
            vector<HoldEmRank> fx1, fx2;
            for (const auto& rc1 : rankCount1)
                fx1.push_back(rc1.first);
            for (const auto& rc2 : rankCount2)
                fx2.push_back(rc2.first);

            sort(fx1.begin(), fx1.end(), compareHoldEmRank);
            sort(fx2.begin(), fx2.end(), compareHoldEmRank);

            for (size_t i = 0; i < fx1.size(); ++i)
                if (fx1[i] != fx2[i])
                    return fx1[i] < fx2[i];
            break;
	}

        case HoldEmHandRank::fourofakind: {
	    // Store the rank of four
            HoldEmRank Four1, Four2;

            for (const auto& rc1 : rankCount1) 
                if (rc1.second == 4)
                    Four1 = rc1.first;

            for (const auto& rc2 : rankCount2)
                if (rc2.second == 4)
                    Four2 = rc2.first;

            if (Four1 != Four2)
                return Four1 < Four2;
            break;
	}

	default:
	    break;
    }
    return false;
}
