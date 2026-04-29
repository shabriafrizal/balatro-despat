#pragma once

#include <vector>

// Card representation
struct Card
{
    enum class Suit
    {
        HEARTS,
        DIAMONDS,
        CLUBS,
        SPADES
    };

    enum class Rank
    {
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9,
        TEN = 10,
        JACK = 11,
        QUEEN = 12,
        KING = 13,
        ACE = 14
    };

    Suit suit;
    Rank rank;
};

// Hand representation - a collection of cards
class Hand
{
public:
    Hand();
    virtual ~Hand() = default;

    void addCard(const Card &card);
    void removeCard(size_t index);
    const std::vector<Card> &getCards() const;
    size_t getCardCount() const;
    void clear();

private:
    std::vector<Card> cards;
};
