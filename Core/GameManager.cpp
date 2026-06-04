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

#include "SkipReward/RunSessionState.h"
#include "SkipReward/CommandTiming.h"

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
    // Execute any queued NextBlind rewards
    executePendingCommands(SkipReward::CommandTiming::NextBlind);

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

void GameManager::executePendingCommands(SkipReward::CommandTiming timing)
{
    SkipReward::RunSessionState state{
        handsRemaining,
        discardsRemaining,
        money,
        freeRerolls};

    commandQueue.executeCommandsWithTiming(timing, state);
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
                // Enqueue skip rewards from the current blind state
                blindManager.queueSkipRewards(commandQueue);

                // Execute Immediate commands right away
                executePendingCommands(SkipReward::CommandTiming::Immediate);

                // Show what was gained
                std::cout << "\nSkipping " << blindManager.getCurrentBlindName()
                          << " — gaining skip rewards!\n";
                {
                    const auto &pending = commandQueue.getPendingCommands();
                    for (const auto &cmd : pending)
                    {
                        if (cmd.executed)
                            std::cout << "  + " << cmd.command->getDescription() << "\n";
                    }
                }

                blindManager.skipBlind();

                // Execute NextBlind commands at the start of the next blind
                executePendingCommands(SkipReward::CommandTiming::NextBlind);

                startBlind();
                continue; // re-evaluate skip prompt for the next blind
            }
        }

        // Draw to full hand at start of each blind iteration
        // (currentHand may have cards from previous blind that need replenishing)
        drawToHand(8);

        while (handsRemaining > 0)
        {
            std::cout << "\n=== Hands: "
                      << handsRemaining
                      << " | Discards: "
                      << discardsRemaining
                      << " | Money: $"
                      << money
                      << " | Score: "
                      << blindRule.getAccumulatedScore()
                      << " / " << blindRule.getRequiredScore()
                      << " ===\n";

            displayCurrentHand();

            // Prompt for card indices first
            std::cout << "\nEnter card indices (space-separated):\n> ";
            std::string indexInput;
            std::getline(std::cin, indexInput);

            std::vector<size_t> indices;
            {
                std::istringstream iss(indexInput);
                size_t idx;
                size_t maxIdx = currentHand.getCardCount();
                while (iss >> idx)
                {
                    if (idx < maxIdx)
                        indices.push_back(idx);
                    else
                        std::cerr << "Warning: Index " << idx << " out of range, skipping...\n";
                }
            }

            if (indices.empty())
            {
                std::cout << "No valid indices entered.\n";
                continue;
            }

            // Then choose what to do with them
            std::cout << "[P]lay selected  [D]iscard selected\n> ";
            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "P" || choice == "p")
            {
                int score = handPlayer.handlePlayWithIndices(
                    currentHand, deck, chooseHand,
                    scoringRule, jokerManager, handsRemaining, indices);

                if (score < 0)
                {
                    continue; // invalid play, retry
                }

                blindRule.addScore(score);
                int accumulated = blindRule.getAccumulatedScore();
                int required = blindRule.getRequiredScore();
                std::cout << "Blind progress: " << accumulated << " / " << required << "\n";

                if (blindRule.isBlindCleared())
                {
                    std::cout << "\n*** " << blindManager.getCurrentBlindName()
                              << " cleared! ***\n";

                    int reward = blindManager.getReward();
                    money += reward;
                    std::cout << "+$" << reward << " reward earned!\n";

                    blindManager.advanceBlind(true);

                    // Execute any queued NextAnte rewards after ante may have incremented
                    executePendingCommands(SkipReward::CommandTiming::NextAnte);

                    // Execute any queued NextShop rewards before entering shop
                    executePendingCommands(SkipReward::CommandTiming::NextShop);

                    // Display shop after defeating a blind
                    shop.displayAndHandle(jokerManager, money);

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
                handPlayer.handleDiscardWithIndices(
                    currentHand, deck, chooseHand,
                    discardsRemaining, indices);
            }
            else
            {
                std::cout << "Invalid choice. Enter P to play or D to discard.\n";
            }
        }
    }
}
