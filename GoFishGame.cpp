#include "GoFishGame.h"

static const int LEAST_NUM = 4;
static const int startIndex = 2;
static const int LEAST_PLAYERS = 2;
static const int cardsPerPlayerTwoPlayers = 7;
static const int cardsPerPlayerMoreThanTwo = 5;

// template specialization for HoldEm
template<>
GoFishGame<suits, HoldEmRank, HoldEmDeck>::GoFishGame(int argc, const char *argv[]) : Game(argc, argv){
    GameID = 0;
    Deck = HoldEmDeck();
    for (auto rank = HoldEmRank::Two; rank != HoldEmRank::Undefined; ++rank) {
        int count = count_if(Deck.begin(), Deck.end(), [rank](const auto &card) {return card.Rank == rank;});

        if (count < LEAST_NUM) throw runtime_error("Invalid card number per rank for Go Fish Game.");
    }

    // create hands
    hands.resize(players.size());
    // create books
    books.resize(players.size());
    // store the number of books
    booksNum.resize(players.size());
}

// template specialization for Pinochle 
template<>
GoFishGame<suits, PinochleRank, PinochleDeck>::GoFishGame(int argc, const char *argv[]) : Game(argc, argv){
    GameID = 1;
    Deck = PinochleDeck();
    for (auto rank = PinochleRank::Nine; rank != PinochleRank::Undefined; ++rank) {
        int count = count_if(Deck.begin(), Deck.end(), [rank](const auto &card) {return card.Rank == rank;});

        if (count < LEAST_NUM) throw runtime_error("Invalid card number per rank for Go Fish Game.");
    }

    // create hands
    hands.resize(players.size());
    // create books
    books.resize(players.size());
    // store the number of books
    booksNum.resize(players.size());
}

// template specialization for Uno 
template<>
GoFishGame<Color, UnoRank, UnoDeck>::GoFishGame(int argc, const char *argv[]) : Game(argc, argv){
    GameID = 2;
    Deck = UnoDeck();
    for (auto rank = UnoRank::Zero; rank != UnoRank::Undefined; ++rank) {
        int count = count_if(Deck.begin(), Deck.end(), [rank](const auto &card) {return card.Rank == rank;});

        if (count < LEAST_NUM) throw runtime_error("Invalid card number per rank for Go Fish Game.");
    }

    // create hands
    hands.resize(players.size());
    // create books
    books.resize(players.size());
    // store the number of books
    booksNum.resize(players.size());
}

template<typename S, typename R, typename D>
bool GoFishGame<S, R, D>::collect_books(size_t playerNum) {
    if (playerNum < 1 || playerNum > hands.size())
        throw out_of_range("Invalid player number.");

    auto& hand = hands[playerNum - 1];

    for (R rank = static_cast<R>(0); rank != R::Undefined; ++rank) {
        size_t count = count_if(hand.begin(), hand.end(), [rank](const Card<R, S> &card){return card.Rank == rank;});

        if (count == LEAST_NUM) {
            // create the predicate lambda function
            auto predicate = [rank](const Card<R, S> &card) {return card.Rank == rank;};

            // collect the 4-of-a-kind from hand to book
            books[playerNum - 1].collect_if(hand, predicate);

            booksNum[playerNum - 1] += 1;

            return true;
        }
    }
    return false;
}

template <typename S, typename R, typename D>
bool GoFishGame<S, R, D>::turn(size_t playerNum) {
    if (playerNum < 1 || playerNum > hands.size())
        throw out_of_range("Invalid player number.");

    cout << "******************************************************" << endl;
    cout << players[playerNum - 1] << "'s turn." << "Player ID: " << playerNum << endl;
    cout << "******************************************************" << endl;

    for (size_t num = 0; num < hands.size(); ++num) {
        cout << "Player ID: " << num + 1 << endl;
        cout << "Cards for now: " << endl;

        // print out hand
        for (auto it = hands[num].begin(); it != hands[num].end(); ++it)
            cout << *it << " ";
        cout << endl;

        cout << "Book for now: " << endl;

        // print out book
        for (auto it = books[num].begin(); it != books[num].end(); ++it)
            cout << *it << " ";
        cout << endl;
    }

    cout << "Please provides a valid card rank and player number." << endl;
    if (GameID == 0)
        cout << "In the HoldEm game, cardRank should be between 0-12, " 
             << "representing Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace." << endl;
    else if (GameID == 1)
        cout << "In the Pinochle game, cardRank should be between 0-5, representing Nine, Jack, Queen, King, Ten, Ace." << endl;
    else
        cout << "In the Uno game, cardRank should be between 0-15, representing Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Skip, Reverse, Drawtwo, Drawfour, Wild, Blank." << endl;
    
    int cardRank;
    bool cardRankVal = false;
    size_t targetID;
    bool targetIDVal = false;
    while (true) {
    	cout << "Please input two integers, the first one is cardRank, the second one is targetID" << endl;
    	cin >> cardRank >> targetID;

    	if (GameID == 0) {
            if (cardRank < 0 || cardRank > 12) {
                cout << "Invalid cardRank, in HoldEm, it should be between 0-12!";
		cardRankVal = false;
            } else {
		cardRankVal = true;
	    }
        }
    
        else if (GameID == 1) {
            if (cardRank < 0 || cardRank > 5) {
                cout << "Invalid cardRank, in Pinochle, it should be between 0-5!";
		cardRankVal = false;
            } else {
		cardRankVal = true;
	    }
        }

        if (GameID == 2) {
            if (cardRank < 0 || cardRank > 15) {
                cout << "Invalid cardRank, in Uno, it should be between 0-15!";
		cardRankVal = false;
            } else {
		cardRankVal = true;
	    }
        }

        if (targetID < 1 || targetID > hands.size()) {
            cout << "Invalid targetID, it should be between 1-" << hands.size() << endl;
	    targetIDVal = false;
        } else {
	    targetIDVal = true;
        }

        if (cardRankVal && targetIDVal)
	    break;

	// clear the input
        cin.clear();
	// Ignore invalid input until next newline character
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }

    // Request the target player for certain rank
    bool rq = hands[playerNum - 1].request(hands[targetID - 1], static_cast<R>(cardRank));
    
    if (rq == true) {
        cout << "request successfully!" << endl;

        int booksAdded = 0;
        while (collect_books(playerNum)) ++booksAdded;
        cout << booksAdded << "books has been added for " << players[playerNum - 1] << ", with PlayerID: " << playerNum << endl;

        return true;
    } else {
        if (Deck.isEmpty()) {
            cout << "request failed and the Deck is empty for now, you are out!" << endl;
            // have all their cards moved into the deck
            Deck.collect(hands[playerNum - 1]);
            outPlayer[playerNum] = players[playerNum - 1];
            return false;
        } else {
            cout << "request failed, you can draw a card from deck." << endl;
            Deck >> hands[playerNum - 1];
            return (*(hands[playerNum - 1].end() - 1)).Rank == static_cast<R>(cardRank);
        }
    }
}

template<typename S, typename R, typename D>
void GoFishGame<S, R, D>::deal() {
    // Determine number of cards to deal
    int numCardsToDeal = hands.size() > LEAST_PLAYERS ? cardsPerPlayerMoreThanTwo : cardsPerPlayerTwoPlayers;

    // Shuffle the deck
    Deck.shuffle();

    // Deal the cards
    for (int i = 0; i < numCardsToDeal; ++i) 
        for (auto& hand : hands)
            if (!Deck.isEmpty())
                Deck >> hand;
}

template <typename S, typename R, typename D>
int GoFishGame<S, R, D>::play() {
    // Initial dealing of cards
    deal();

    // Collect initial books
    for (size_t playerNum = 1; playerNum < hands.size() + 1; ++playerNum) {
        while (collect_books(playerNum)) {}
    }

    int roundNum = 0;
    bool gameEnd = false;

    // Main game loop
    while (!gameEnd) {
        for (size_t playerNum = 1; playerNum < hands.size() + 1; ++playerNum) {
            auto it = outPlayer.find(playerNum);
            // Check if player is still in the game
            if (it == outPlayer.end()) {
                while (turn(playerNum)) {
		    cout << "Round " << ++roundNum << " end." << endl;
		}
            }
        }

        bool Empty = true;

        for (size_t playerNum = 1; playerNum < hands.size() + 1; ++playerNum) {
            // Empty will be true only when all hands are empty
            Empty = Empty && hands[playerNum - 1].isEmpty();
            cout << "Player " << playerNum << " has made "
                      << booksNum[playerNum - 1] << " books." << endl;
        }

        // Empty will be true only when all hands and Deck are empty
        Empty = Empty && Deck.isEmpty();

        // Check termination conditions
        if (Empty || hands.size() - outPlayer.size() < 2) {
            gameEnd = true;
        }

        if (gameEnd == true) {
            auto maxIt = std::max_element(booksNum.begin(), booksNum.end());

            if (maxIt != booksNum.end()) {
                int maxValue = *maxIt;
                cout << "Game over, Player(s): ";
                for (size_t i = 0; i < booksNum.size(); ++i) {
                    if (booksNum[i] == maxValue) {
                        std::cout << " " << i + 1;
                    }
                }
		cout << "Win!!!" << endl;
            }
        }
    }

    return 0;
}
