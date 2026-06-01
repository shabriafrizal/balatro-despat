#include <iostream>
#include <memory>
#include <algorithm>
#include <array>
#include <random>
#include <sstream>

#include "GameManager.h"
#include "Jokers/FlatChipJoker.h"
#include "Jokers/PairJoker.h"

namespace
{
    const std::array<Card::Suit, 4> kSuits = {
        Card::Suit::HEARTS,
        Card::Suit::DIAMONDS,
        Card::Suit::CLUBS,
        Card::Suit::SPADES};

    const std::array<Card::Rank, 13> kRanks = {
        Card::Rank::TWO, Card::Rank::THREE, Card::Rank::FOUR, Card::Rank::FIVE,
        Card::Rank::SIX, Card::Rank::SEVEN, Card::Rank::EIGHT, Card::Rank::NINE,
        Card::Rank::TEN, Card::Rank::JACK, Card::Rank::QUEEN, Card::Rank::KING,
        Card::Rank::ACE};

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

void GameManager::setupJokers()
{
    jokerManager.clear();
    jokerManager.addJoker(std::make_unique<PairJoker>());
    jokerManager.addJoker(std::make_unique<FlatChipJoker>());
}

void GameManager::buildAndShuffleDeck()
{
    deck.clear();
    deck.reserve(kSuits.size() * kRanks.size());
    for (Card::Suit suit : kSuits)
    {
        for (Card::Rank rank : kRanks)
        {
            deck.push_back(Card{suit, rank});
        }
    }
    std::random_device randomDevice;
    std::mt19937 rng(randomDevice());
    std::shuffle(deck.begin(), deck.end(), rng);
}

void GameManager::drawToHand(size_t targetCount)
{
    while (currentHand.getCardCount() < targetCount && !deck.empty())
    {
        currentHand.addCard(deck.back());
        deck.pop_back();
    }
}

void GameManager::displayCurrentHand() const
{
    std::cout << "\nYour hand:\n";
    const std::vector<Card> &cards = currentHand.getCards();
    for (size_t i = 0; i < cards.size(); ++i)
    {
        const Card &card = cards[i];
        std::cout << "[" << i << "] " << rankToString(card.rank) << " of " << suitToString(card.suit) << "\n";
    }
}

void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";

    setupJokers();

    buildAndShuffleDeck();

    currentHand.clear();
    drawToHand(8);

    handsRemaining = 4;
    discardsRemaining = 3;
    runWon = false;

    std::cout << "[Debug] Dealt "
              << currentHand.getCardCount()
              << " cards, "
              << deck.size()
              << " remaining in deck\n";

    while (handsRemaining > 0)
    {
        displayCurrentHand();

        std::cout << "\nHands: "
                  << handsRemaining
                  << " | Discards: "
                  << discardsRemaining
                  << "\n";

        std::cout << "[P]lay  [D]iscard\n";
        std::cout << "> ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "P" || choice == "p")
        {
            bool won = handPlayer.handlePlay(
                currentHand, deck, chooseHand,
                scoringRule, blindRule, rewardRule,
                jokerManager, handsRemaining);

            if (won)
            {
                runWon = true;
                return;
            }
        }
        else if (choice == "D" || choice == "d")
        {
            handPlayer.handleDiscard(
                currentHand, deck, chooseHand,
                discardsRemaining);
        }
        else
        {
            std::cout
                << "Invalid choice. Enter P to play or D to discard.\n";
        }
    }

    std::cout << "\nNo hands remaining — you lose!\n";
    std::cout << "=== Run Ended (Lose) ===\n";
}
