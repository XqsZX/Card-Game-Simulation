// definitions for CardSet.h

// print out the cards
template <typename R, typename S>
void CardSet<R, S>::print(ostream &os, size_t s) const {
    // a counter for a column
    size_t count = 0;
    // traverse all cards
    for (auto it = CardSet<R, S>::cards.begin(); it != CardSet<R, S>::cards.end(); ++it) {
	os << *it << " ";
	if (++count % s == 0) os << endl;
    }
	if (count % s != 0) os << endl;    
}

template <typename R, typename S>
CardSet<R, S> &CardSet<R, S>::operator>>(CardSet<R, S> &cs) {
    if (isEmpty())
	throw runtime_error("Error: no card left.");

    try {
	cs.cards.push_back(cards.back());
	cards.pop_back();
    }
    
    catch (const exception& e) {
	cout << "Exception Caught" << endl;
	cout << e.what() << endl;
    }

    // return reference to this
    return *this;
}

// find out whether the cardSet is empty or not
template <typename R, typename S>
bool CardSet<R, S>::isEmpty() {
    return CardSet<R, S>::cards.empty();
}

template <typename R, typename S>
CardSet<R, S>::CardSet(const CardSet<R, S>& cs) : cards(cs.cards) {}

// return cards
// template <typename R, typename S>
// vector<Card<R, S>> CardSet<R, S>::*CardSet<R, S>::getCards() {
//    return &CardSet<R, S>::cards;
// }

template<typename R, typename S>
void CardSet<R, S>::sort() {
    sort(begin(), end(), lowerRank<R, S>);
}

template<typename R, typename S>
void CardSet<R, S>::collect(CardSet<R, S> &cs) {
    move(cs.begin(), cs.end(), back_inserter(cards));
    cs.cards.clear();
}

template<typename R, typename S>
void CardSet<R, S>::collect_if(CardSet<R, S>& deck, function<bool(Card<R, S>&)> predicate) {
    copy_if(deck.begin(), deck.end(), back_inserter(cards), predicate);
    auto newEnd = remove_if(deck.begin(), deck.end(), predicate);
    deck.cards.erase(newEnd, deck.end());
}

template<typename R, typename S>
bool CardSet<R, S>::request(CardSet<R, S>& cs, R rank) {
    auto it = find_if(cs.begin(), cs.end(), [rank](const Card<R, S>& card) {return card.Rank == rank;});

    if (it != cs.end()) {
        // Move matched card to cards
        CardSet<R, S>::cards.push_back(move(*it));
        // Remove matched card from other
        cs.cards.erase(it);
        return true;
    }

    return false;
}
