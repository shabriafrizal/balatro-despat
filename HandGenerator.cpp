#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "HandGenerator.h"

namespace
{
    const std::array<Card::Suit, 4> kSuits = {
        Card::Suit::HEARTS,
        Card::Suit::DIAMONDS,
        Card::Suit::CLUBS,
        Card::Suit::SPADES};

    const std::array<Card::Rank, 13> kRanks = {
        Card::Rank::TWO,
        Card::Rank::THREE,
        Card::Rank::FOUR,
        Card::Rank::FIVE,
        Card::Rank::SIX,
        Card::Rank::SEVEN,
        Card::Rank::EIGHT,
        Card::Rank::NINE,
        Card::Rank::TEN,
        Card::Rank::JACK,
        Card::Rank::QUEEN,
        Card::Rank::KING,
        Card::Rank::ACE};

    std::vector<Card> buildDeck()
    {
        std::vector<Card> deck;
        deck.reserve(kSuits.size() * kRanks.size());

        for (Card::Suit suit : kSuits)
        {
            for (Card::Rank rank : kRanks)
            {
                deck.push_back(Card{suit, rank});
            }
        }

        return deck;
    }

    const char *suitToString(Card::Suit suit)
    {
        switch (suit)
        {
        case Card::Suit::HEARTS:
            return "Hearts";
        case Card::Suit::DIAMONDS:
            return "Diamonds";
        case Card::Suit::CLUBS:
            return "Clubs";
        case Card::Suit::SPADES:
            return "Spades";
        default:
            return "Unknown";
        }
    }

    const char *rankToString(Card::Rank rank)
    {
        switch (rank)
        {
        case Card::Rank::TWO:
            return "2";
        case Card::Rank::THREE:
            return "3";
        case Card::Rank::FOUR:
            return "4";
        case Card::Rank::FIVE:
            return "5";
        case Card::Rank::SIX:
            return "6";
        case Card::Rank::SEVEN:
            return "7";
        case Card::Rank::EIGHT:
            return "8";
        case Card::Rank::NINE:
            return "9";
        case Card::Rank::TEN:
            return "10";
        case Card::Rank::JACK:
            return "J";
        case Card::Rank::QUEEN:
            return "Q";
        case Card::Rank::KING:
            return "K";
        case Card::Rank::ACE:
            return "A";
        default:
            return "?";
        }
    }
}

Hand HandGenerator::generateHand(size_t cardCount)
{
    std::cout << "Generating cards for player...\n";

    std::vector<Card> deck = buildDeck();
    std::random_device randomDevice;
    std::mt19937 rng(randomDevice());
    std::shuffle(deck.begin(), deck.end(), rng);

    if (cardCount > deck.size())
    {
        cardCount = deck.size();
    }

    Hand hand;
    for (size_t i = 0; i < cardCount; ++i)
    {
        hand.addCard(deck[i]);
    }

    std::cout << "Hand:\n";
    const std::vector<Card> &cards = hand.getCards();
    for (size_t i = 0; i < cards.size(); ++i)
    {
        const Card &card = cards[i];
        std::cout << "[" << i << "] " << rankToString(card.rank) << " of " << suitToString(card.suit) << "\n";
    }

    return hand;
}