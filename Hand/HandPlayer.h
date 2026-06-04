#pragma once

#include <vector>
#include <cstddef>
#include <string>

class Hand;
class ChooseHand;
class ScoringRule;
class BlindRule;
class RewardRule;
class JokerManager;
struct Card;

class HandPlayer
{
public:
    // Returns the score of the played hand, or -1 if no play occurred
    int handlePlay(Hand &currentHand, std::vector<Card> &deck,
                   ChooseHand &chooseHand, ScoringRule &scoringRule,
                   JokerManager &jokerManager, int &handsRemaining);

    // Same as handlePlay but uses pre-selected indices (no prompt)
    int handlePlayWithIndices(Hand &currentHand, std::vector<Card> &deck,
                              ChooseHand &chooseHand, ScoringRule &scoringRule,
                              JokerManager &jokerManager, int &handsRemaining,
                              const std::vector<size_t> &indices);

    void handleDiscard(Hand &currentHand, std::vector<Card> &deck,
                       ChooseHand &chooseHand, int &discardsRemaining);

    // Same as handleDiscard but uses pre-selected indices (no prompt)
    void handleDiscardWithIndices(Hand &currentHand, std::vector<Card> &deck,
                                  ChooseHand &chooseHand, int &discardsRemaining,
                                  const std::vector<size_t> &indices);

private:
    std::vector<size_t> promptCardSelection(
        const std::string &message,
        const Hand &currentHand) const;

    void removeCardsFromHand(
        Hand &currentHand,
        std::vector<size_t> indices) const;

    int resolvePlayedHand(
        const Hand &playedHand,
        ScoringRule &scoringRule,
        JokerManager &jokerManager);

    void drawToHand(
        Hand &currentHand,
        std::vector<Card> &deck,
        size_t targetCount) const;
};