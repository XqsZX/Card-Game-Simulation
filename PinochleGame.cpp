#include "PinochleGame.h"

# define startIndex 2
# define packet 3
# define Length 12
# define SUCCESS 0
# define Pinochle_suit_size 5
# define Pinochle_rank_size 7

const vector<unsigned int> PinochleGame::values_PinochleMelds = {10, 20, 40, 40, 40, 60, 80, 100, 150, 300, 400, 600, 800, 1000, 1500};

PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv) {
    // create hands
    hands.resize(argc - startIndex);
}

void PinochleGame::deal() {
    try {
        for (int i = 0; !pd.isEmpty(); i = (i + 1) % hands.size()) {
        for (int j = 0; j < packet && !pd.isEmpty(); ++j)
        pd >> hands[i];
        }
    }
    catch (const runtime_error& e) {
    cerr << "Caught exception: " << e.what() << endl;
    }
}

void PinochleGame::print(ostream& os, const size_t len) {
    for (size_t i = 0; i < hands.size(); ++i) {
        os << "Player: " << players[i] << endl;
        hands[i].print(os, len);

        // Print out Melds
        vector<PinochleMelds> pm;
        suit_independent_evaluation(hands[i], pm);
        cout << "Pinochle Melds in your hand: ";
        for (auto Meld : pm)
            cout << " " << Meld;
        cout << endl;
    }
}

void PinochleGame::collectCards() {
    for (auto it = hands.begin(); it != hands.end(); ++it)
    pd.collect(*it);
}

string PinochleGame::ask(ostream& os, istream& is) {
    os << "Want to end this Game? (yes or no): " << endl;
    string answer;
    is >> answer;

    return answer;  
}

int PinochleGame::play() {
    cout << "Pinochle begin" << endl;
    
    while (true) {
    // call the deck's shuffle member function
    pd.shuffle();
    // call the deal member function to distribute the cards to the players
    deal();
    // print out each player's name and then the cards in their hand
    print(cout, Length);
    // move the cards back out of each player's hand into the deck
    collectCards();
    // asks the user whether or not to end the game
    if (ask(cout, cin) == "yes")
        // if that string is "yes", return a value to indicate success
        return SUCCESS;
    }
}

ostream& operator<<(ostream& os, const PinochleMelds& pm) {
    switch (pm) {
    case PinochleMelds::dix:
        os << "dix";
        break;
    case PinochleMelds::offsuitmarriage:
        os << "offsuitmarriage";
        break;
    case PinochleMelds::fortyjacks:
        os << "fortyjacks";
        break;
    case PinochleMelds::pinochle:
        os << "pinochle";
        break;
    case PinochleMelds::insuitmarriage:
        os << "insuitmarriage";
        break;
    case PinochleMelds::sixtyqueens:
        os << "sixtyqueens";
        break;
    case PinochleMelds::eightykings:
        os << "eightykings";
        break;
    case PinochleMelds::hundredaces:
        os << "hundredaces";
        break;
    case PinochleMelds::insuitrun:
        os << "insuitrun";
        break;
    case PinochleMelds::doublepinochle:
        os << "doublepinochle";
        break;
    case PinochleMelds::fourhundredjacks:
        os << "fourhundredjacks";
        break;
    case PinochleMelds::sixhundredqueens:
        os << "sixhundredqueens";
        break;
    case PinochleMelds::eighthundredkings:
        os << "eighthundredkings";
        break;
    case PinochleMelds::thousandaces:
        os << "thousandaces";
        break;
    case PinochleMelds::insuitdoublerun:
        os << "insuitdoublerun";
        break;
    }
    return os;
}

void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank, suits>& cs, vector<PinochleMelds>& pm) {
    // Make an independent copy 
    CardSet<PinochleRank, suits> cs0(cs);
    vector<Card<PinochleRank, suits>> vc(cs0.begin(), cs0.end());

    vector<vector<int>> cardCount(Pinochle_rank_size, vector<int>(Pinochle_suit_size, 0));
    // Count cards
    for (auto c : vc)
        ++cardCount[static_cast<int>(c.Rank)][static_cast<int>(c.Suit)];

    // Aces
    if (cardCount[5][0] + cardCount[5][1] + cardCount[5][2] + cardCount[5][3] == 8) {
        pm.push_back(PinochleMelds::thousandaces);
    } else if (cardCount[5][0] && cardCount[5][1] && cardCount[5][2] && cardCount[5][3]) {
        pm.push_back(PinochleMelds::hundredaces);
    } else {

    }

    // Kings
    if (cardCount[3][0] + cardCount[3][1] + cardCount[3][2] + cardCount[3][3] == 8) {
        pm.push_back(PinochleMelds::eighthundredkings);
    } else if (cardCount[3][0] && cardCount[3][1] && cardCount[3][2] && cardCount[3][3]) {
        pm.push_back(PinochleMelds::eightykings);
    } else {

    }

    // Queens
    if (cardCount[2][0] + cardCount[2][1] + cardCount[2][2] + cardCount[2][3] == 8) {
        pm.push_back(PinochleMelds::sixhundredqueens);
    } else if (cardCount[2][0] && cardCount[2][1] && cardCount[2][2] && cardCount[2][3]) {
        pm.push_back(PinochleMelds::sixtyqueens);
    } else {

    }

    // Jacks
    if (cardCount[1][0] + cardCount[1][1] + cardCount[1][2] + cardCount[1][3] == 8) {
        pm.push_back(PinochleMelds::fourhundredjacks);
    } else if (cardCount[1][0] && cardCount[1][1] && cardCount[1][2] && cardCount[1][3]) {
        pm.push_back(PinochleMelds::fortyjacks);
    } else {

    }

    // Double Pinochle
    if (cardCount[1][1] + cardCount[2][3] == 4) {
        pm.push_back(PinochleMelds::doublepinochle);
    } else if (cardCount[1][1] && cardCount[2][3]) {
        pm.push_back(PinochleMelds::pinochle);
    } else {

    }
}
