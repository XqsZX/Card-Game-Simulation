template <typename R, typename S>
// shuffle the card with seed mt19937
void Deck<R, S>::shuffle() {
    // reorder the card
    random_device rd;
    mt19937 mt_rand(rd());
    std::shuffle(CardSet<R, S>::cards.begin(), CardSet<R, S>::cards.end(), mt_rand);
}

