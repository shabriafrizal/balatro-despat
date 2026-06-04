#include <iostream>
#include <memory>
#include <algorithm>
#include <array>
#include <random>
#include <sstream>

#include "GameManager.h"
#include "Joker/FlatChipJoker.h"
#include "Joker/PairJoker.h"
#include "Joker/MultiplierJoker.h"

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

void GameManager::startBlind()
{
    blindRule.reset();
    blindRule.setRequiredScore(blindManager.getRequiredScore());
    handsRemaining = 4;
    discardsRemaining = 3;

    std::cout << "\n========== " << blindManager.getCurrentBlindName()
              << " (Ante " << blindManager.getAnteLevel() << ") ==========\n";
    std::cout << "Required score: " << blindRule.getRequiredScore()
              << " | Reward: " << blindManager.getReward() << "\n";
    std::cout << "============================================\n";
}

bool GameManager::tryPlayHand()
{
    int score = handPlayer.handlePlay(
        currentHand, deck, chooseHand,
        scoringRule, jokerManager, handsRemaining);

    if (score < 0)
    {
        return false; // no valid play
    }

    // Accumulate score toward the blind requirement
    blindRule.addScore(score);
    int accumulated = blindRule.getAccumulatedScore();
    int required = blindRule.getRequiredScore();
    std::cout << "Blind progress: " << accumulated << " / " << required << "\n";

    if (blindRule.isBlindCleared())
    {
        std::cout << "\n*** " << blindManager.getCurrentBlindName()
                  << " cleared! ***\n";
        return true;
    }

    return false;
}

void GameManager::tryDiscard()
{
    handPlayer.handleDiscard(
        currentHand, deck, chooseHand,
        discardsRemaining);
}

void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";

    setupJokers();
    buildAndShuffleDeck();
    blindManager.initializeProgression();

    startBlind();

    while (true)
    {
        // Ask to skip the blind BEFORE entering play/discard (Balatro-style)
        if (blindManager.canSkipCurrentBlind())
        {
            std::cout << "\nDo you want to skip " << blindManager.getCurrentBlindName()
                      << "? (Forfeit reward of " << blindManager.getReward() << ")\n";
            std::cout << "[S]kip  [C]ontinue\n";
            std::cout << "> ";

            std::string skipChoice;
            std::getline(std::cin, skipChoice);

            if (skipChoice == "S" || skipChoice == "s")
            {
                std::cout << "\nSkipping " << blindManager.getCurrentBlindName()
                          << " — but gaining skip rewards!\n";
                std::cout << "+1 Hand | +1 Discard | +10 Money\n";
                handsRemaining += 1;
                discardsRemaining += 1;
                money += 10;
                blindManager.skipBlind();
                startBlind();
                continue; // re-evaluate skip prompt for the next blind
            }
        }

        // Draw to full hand at start of each blind iteration
        // (currentHand may have cards from previous blind that need replenishing)
        drawToHand(8);

        while (handsRemaining > 0)
        {
            displayCurrentHand();

            std::cout << "\nHands: "
                      << handsRemaining
                      << " | Discards: "
                      << discardsRemaining
                      << " | Money: "
                      << money
                      << " | Score: "
                      << blindRule.getAccumulatedScore()
                      << " / " << blindRule.getRequiredScore()
                      << "\n";

            std::cout << "[P]lay  [D]iscard\n";
            std::cout << "> ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "P" || choice == "p")
            {
                bool blindCleared = tryPlayHand();

                if (blindCleared)
                {
                    blindManager.advanceBlind(true);

                    // Display shop after defeating a blind
                    shop.displayAndHandle(jokerManager);

                    startBlind();
                    break; // exit inner loop, start next blind
                }

                if (handsRemaining == 0)
                {
                    std::cout << "\nNo hands remaining — you lose!\n";
                    std::cout << "=== Run Ended (Lose) ===\n";
                    return;
                }
            }
            else if (choice == "D" || choice == "d")
            {
                tryDiscard();
            }
            else
            {
                std::cout << "Invalid choice. Enter P to play or D to discard.\n";
            }
        }
    }
}
