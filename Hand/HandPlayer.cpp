#include <iostream>
#include <algorithm>
#include <sstream>

#include "HandPlayer.h"
#include "Hand.h"
#include "ChooseHand.h"
#include "Scoring/ScoringRule.h"
#include "Joker/JokerManager.h"
#include "Scoring/ScoreContext.h"
#include "HandRankUtils.h"

namespace
{
    std::vector<size_t> readIndices(size_t maxIndex)
    {
        std::vector<size_t> indices;
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        size_t index;
        while (iss >> index)
        {
            if (index < maxIndex)
            {
                indices.push_back(index);
            }
            else
            {
                std::cerr << "Warning: Index " << index << " out of range, skipping...\n";
            }
        }
        return indices;
    }
}

int HandPlayer::handlePlay(
    Hand &currentHand,
    std::vector<Card> &deck,
    ChooseHand &chooseHand,
    ScoringRule &scoringRule,
    JokerManager &jokerManager,
    int &handsRemaining)
{
    auto indices = promptCardSelection(
        "Enter card indices to PLAY (space-separated):",
        currentHand);

    if (indices.empty())
    {
        std::cerr << "No valid cards selected!\n";
        return -1;
    }

    if (indices.size() > 5)
    {
        std::cout << "You can only play up to 5 cards!\n";
        return -1;
    }

    Hand playedHand =
        chooseHand.chooseFromHand(
            currentHand, indices);

    removeCardsFromHand(currentHand, indices);

    int score = resolvePlayedHand(
        playedHand, scoringRule, jokerManager);

    handsRemaining--;

    if (handsRemaining > 0)
    {
        drawToHand(currentHand, deck, 8);
    }

    return score;
}

int HandPlayer::handlePlayWithIndices(
    Hand &currentHand,
    std::vector<Card> &deck,
    ChooseHand &chooseHand,
    ScoringRule &scoringRule,
    JokerManager &jokerManager,
    int &handsRemaining,
    const std::vector<size_t> &indices)
{
    if (indices.empty())
    {
        std::cerr << "No valid cards selected!\n";
        return -1;
    }

    if (indices.size() > 5)
    {
        std::cout << "You can only play up to 5 cards!\n";
        return -1;
    }

    Hand playedHand =
        chooseHand.chooseFromHand(currentHand, indices);

    removeCardsFromHand(currentHand, indices);

    int score = resolvePlayedHand(playedHand, scoringRule, jokerManager);

    handsRemaining--;

    if (handsRemaining > 0)
    {
        drawToHand(currentHand, deck, 8);
    }

    return score;
}

void HandPlayer::handleDiscard(
    Hand &currentHand,
    std::vector<Card> &deck,
    ChooseHand &chooseHand,
    int &discardsRemaining)
{
    if (discardsRemaining <= 0)
    {
        std::cout << "No discards remaining!\n";
        return;
    }

    auto indices = promptCardSelection(
        "Enter card indices to DISCARD (space-separated):",
        currentHand);

    if (indices.empty())
    {
        std::cerr << "No valid cards selected!\n";
        return;
    }

    currentHand =
        chooseHand.discardFromHand(
            currentHand, indices);

    discardsRemaining--;

    drawToHand(currentHand, deck, 8);

    std::cout
        << "[Debug] Drew back to "
        << currentHand.getCardCount()
        << " cards, "
        << deck.size()
        << " remaining in deck\n";
}

void HandPlayer::handleDiscardWithIndices(
    Hand &currentHand,
    std::vector<Card> &deck,
    ChooseHand &chooseHand,
    int &discardsRemaining,
    const std::vector<size_t> &indices)
{
    if (discardsRemaining <= 0)
    {
        std::cout << "No discards remaining!\n";
        return;
    }

    if (indices.empty())
    {
        std::cerr << "No valid cards selected!\n";
        return;
    }

    currentHand =
        chooseHand.discardFromHand(currentHand, indices);

    discardsRemaining--;

    drawToHand(currentHand, deck, 8);

    std::cout
        << "[Debug] Drew back to "
        << currentHand.getCardCount()
        << " cards, "
        << deck.size()
        << " remaining in deck\n";
}

std::vector<size_t>
HandPlayer::promptCardSelection(
    const std::string &message,
    const Hand &currentHand) const
{
    std::cout << "\n"
              << message
              << "\n";

    std::cout << "> ";

    return readIndices(
        currentHand.getCardCount());
}

void HandPlayer::removeCardsFromHand(
    Hand &currentHand,
    std::vector<size_t> indices) const
{
    std::sort(
        indices.begin(),
        indices.end());

    for (size_t i = indices.size(); i-- > 0;)
    {
        currentHand.removeCard(
            indices[i]);
    }
}

int HandPlayer::resolvePlayedHand(
    const Hand &playedHand,
    ScoringRule &scoringRule,
    JokerManager &jokerManager)
{
    BaseScore baseScore =
        scoringRule.calculateBaseScore(
            playedHand);

    ScoreContext scoreContext;
    scoreContext.hand = &playedHand;
    scoreContext.handType = baseScore.handType;
    scoreContext.chips = baseScore.chips;
    scoreContext.multiplier = baseScore.multiplier;
    scoreContext.recomputeFinalScore();

    jokerManager.applyJokers(scoreContext);

    std::cout
        << "Hand type: "
        << handRankToString(scoreContext.handType)
        << "\n";

    std::cout
        << "Chips: "
        << scoreContext.chips
        << " | Mult: "
        << scoreContext.multiplier
        << "\n";

    std::cout
        << "Final score: "
        << scoreContext.finalScore
        << "\n";

    return scoreContext.finalScore;
}

void HandPlayer::drawToHand(
    Hand &currentHand,
    std::vector<Card> &deck,
    size_t targetCount) const
{
    while (currentHand.getCardCount() < targetCount && !deck.empty())
    {
        currentHand.addCard(deck.back());
        deck.pop_back();
    }
}