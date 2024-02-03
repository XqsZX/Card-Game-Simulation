Lab3

Team Member:
Xin Zhao(xin.zhao1@wustl.edu)

Design Decisions:
1. Use map<int, string> to store the players who has been out of the GoFish game.
2. To figure out which deck players in, I use a int to record, 0 for HoldEm, 1 for Piochle and2 for Uno.
3. Use two bools to record whether the deck and the players' hands are empty, and if both of them are true, end the game.

Errors:
1. /home/warehouse/xin.zhao1/Lab_3/GoFishGame.cpp:158: undefined reference to `CardSet<HoldEmRank, suits>::request(CardSet<HoldEmRank, suits>&, HoldEmRank)'

2. GoFishGame.cpp:106:18:   required from ‘bool GoFishGame<S, R, D>::turn(size_t) [with S = Color; R = UnoRank; D = UnoDeck; size_t = long unsigned int]’
GoFishGame.cpp:219:24:   required from ‘int GoFishGame<S, R, D>::play() [with S = Color; R = UnoRank; D = UnoDeck]’
GoFishGame.h:27:17:   required from here
Card_T.cpp:7:21: error: no match for ‘operator<<’ (operand types are ‘std::ostream’ {aka ‘std::basic_ostream<char>’} and ‘const Color’)
    7 |     os << card.Rank << card.Suit;
      |     ~~~~~~~~~~~~~~~~^~~~~~~~~~~~

3. GoFishGame.cpp:178:41: error: ‘__gnu_cxx::__alloc_traits<std::allocator<CardSet<UnoRank, Color> >, CardSet<UnoRank, Color> >::value_type’ {aka ‘class CardSet<UnoRank, Color>’} has no member named ‘back’
  178 |             return hands[playerNum - 1].back().Rank == static_cast<R>(cardRank);
      |                    ~~~~~~~~~~~~~~~~~~~~~^~~~

Warnings:
1. GoFishGame.cpp:152:34: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<CardSet<UnoRank, Color>, std::allocator<CardSet<UnoRank, Color> > >::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
  152 |     if (targetID < 0 || targetID > hands.size()) {
      |                         ~~~~~~~~~^~~~~~~~~~~~~~

2. GoFishGame.cpp:207:43: warning: comparison of integer expressions of different signedness: ‘int’ and ‘std::vector<CardSet<UnoRank, Color>, std::allocator<CardSet<UnoRank, Color> > >::size_type’ {aka ‘long unsigned int’} [-Wsign-compare]
  207 |         for (int playerNum = 1; playerNum < hands.size() + 1; ++playerNum) {
      |                                 ~~~~~~~~~~^~~~~~~~~~~~~~~~~~

Running the lab2 executable program will generate following output:
case 1:
input:  ./lab3 GoFish
output:
Usage: ./filename GoFish player1 player2 ... (2 ~ 5 players)
Create game failed

case 2:
input: ./lab3 GoFish ksdjsk p1 p2 p3
output: 
GoFish Game's type of deck should be HoldEm, Pinochle or Uno!
Create game failed

Since the output is so long, I will show the important part:
case3:
input:  ./lab3 GoFish Pinochle p1 p2 p3
output:
// Game starts
******************************************************
p1's turn.Player ID: 1
******************************************************
Player ID: 1
Cards for now:
9S AD JS JC 9C
Book for now:

Player ID: 2
Cards for now:
JD 10S QH JS 9H
Book for now:

Player ID: 3
Cards for now:
KC QD 9S 9H AC
Book for now:

Please provides a valid card rank and player number.
In the Pinochle game, cardRank should be between 0-5, representing Nine, Jack, Queen, King, Ten, Ace.
Please input two integers, the first one is cardRank, the second one is targetID
1 2
request successfully!
0books has been added for p1, with PlayerID: 1
Round 1 end.

// A player add a book
******************************************************
p2's turn.Player ID: 2
******************************************************
Player ID: 1
Cards for now:
9S AD 9C 10C
Book for now:
JS JC JD JS
Player ID: 2
Cards for now:
10S QH 9H
Book for now:

Player ID: 3
Cards for now:
KC QD 9S 9H AC
Book for now:

Please provides a valid card rank and player number.
In the Pinochle game, cardRank should be between 0-5, representing Nine, Jack, Queen, King, Ten, Ace.
Please input two integers, the first one is cardRank, the second one is targetID
0 3
request successfully!
0books has been added for p2, with PlayerID: 2
Round 3 end.

// Request successfully
******************************************************
p1's turn.Player ID: 1
******************************************************
Player ID: 1
Cards for now:
10C 10S 10H
Book for now:
JS JC JD JS
Player ID: 2
Cards for now:
QH 9C QD QD JD
Book for now:
9H 9S 9H 9S
Player ID: 3
Cards for now:
KC AC AD AS KS KD 10H
Book for now:

Please provides a valid card rank and player number.
In the Pinochle game, cardRank should be between 0-5, representing Nine, Jack, Queen, King, Ten, Ace.
Please input two integers, the first one is cardRank, the second one is targetID
4 3
request successfully!
1books has been added for p1, with PlayerID: 1
Round 13 end.

// Request failed
******************************************************
p1's turn.Player ID: 1
******************************************************
Player ID: 1
Cards for now:

Book for now:
JS JC JD JS 10C 10S 10H 10H
Player ID: 2
Cards for now:
QH 9C QD QD JD
Book for now:
9H 9S 9H 9S
Player ID: 3
Cards for now:
KC AC AD AS KS KD
Book for now:

Please provides a valid card rank and player number.
In the Pinochle game, cardRank should be between 0-5, representing Nine, Jack, Queen, King, Ten, Ace.
Please input two integers, the first one is cardRank, the second one is targetID
4 3
request failed, you can draw a card from deck.

// End of the game
******************************************************
p3's turn.Player ID: 3
******************************************************
Player ID: 1
Cards for now:

Book for now:
JS JC JD JS 10C 10S 10H 10H 9C 9C 9D 9D 10D 10S 10C 10D QC QC QH QS
Player ID: 2
Cards for now:

Book for now:
9H 9S 9H 9S QH QD QD QS KS KH KD KH
Player ID: 3
Cards for now:
AD JH JD JC AC AS AH JH
Book for now:
AC AD AS AH KC KS KD KC
Please provides a valid card rank and player number.
In the Pinochle game, cardRank should be between 0-5, representing Nine, Jack, Queen, King, Ten, Ace.
Please input two integers, the first one is cardRank, the second one is targetID
5 1
request failed and the Deck is empty for now, you are out!
Player 1 has made 5 books.
Player 2 has made 3 books.
Player 3 has made 2 books.
Game over, Player(s):  1Win!!!

case 4:
input: ./lab3 GoFish Uno p1 p2
output:
// Game starts
******************************************************
p1's turn.Player ID: 1
******************************************************
Player ID: 1
Cards for now:
FiveYellow NineRed SixYellow TwoBlue FourGreen NineGreen ThreeBlue
Book for now:

Player ID: 2
Cards for now:
WildBlack TwoBlue ReverseGreen TwoRed EightBlue DrawTwoRed DrawFourBlack
Book for now:

Please provides a valid card rank and player number.
In the Uno game, cardRank should be between 0-15, representing Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Skip, Reverse, Drawtwo, Drawfour, Wild, Blank.
Please input two integers, the first one is cardRank, the second one is targetID
7 2
request failed, you can draw a card from deck.

// Invalid input
******************************************************
p2's turn.Player ID: 2
******************************************************
Player ID: 1
Cards for now:
FiveYellow NineRed SixYellow TwoBlue FourGreen NineGreen ThreeBlue TwoYellow
Book for now:

Player ID: 2
Cards for now:
WildBlack TwoBlue ReverseGreen TwoRed EightBlue DrawTwoRed DrawFourBlack
Book for now:

Please provides a valid card rank and player number.
In the Uno game, cardRank should be between 0-15, representing Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Skip, Reverse, Drawtwo, Drawfour, Wild, Blank.
Please input two integers, the first one is cardRank, the second one is targetID
16 2
Invalid cardRank, in Uno, it should be between 0-15!Please input two integers, the first one is cardRank, the second one is targetID
7 3
Invalid targetID, it should be between 1-2
Please input two integers, the first one is cardRank, the second one is targetID
7 2
request failed, you can draw a card from deck.
Player 1 has made 0 books.
Player 2 has made 0 books.

case 5:
input:  ./lab3 GoFish HoldEm p1 p2 p3
output:
******************************************************
p1's turn.Player ID: 1
******************************************************
Player ID: 1
Cards for now:
KD KH KC JD 6C
Book for now:

Player ID: 2
Cards for now:
10D 6H JC 4C 10S
Book for now:

Player ID: 3
Cards for now:
7D 4D 5C 5S AS
Book for now:

Please provides a valid card rank and player number.
In the HoldEm game, cardRank should be between 0-12, representing Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace.
Please input two integers, the first one is cardRank, the second one is targetID
6 2
request failed, you can draw a card from deck.
