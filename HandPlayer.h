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
    // Returns true if the run was won
    bool handlePlay(Hand &currentHand, std::vector<Card> &deck,
                    ChooseHand &chooseHand, ScoringRule &scoringRule,
                    BlindRule &blindRule, RewardRule &rewardRule,
                    JokerManager &jokerManager, int &handsRemaining);

    void handleDiscard(Hand &currentHand, std::vector<Card> &deck,
                       ChooseHand &chooseHand, int &discardsRemaining);

private:
    std::vector<size_t> promptCardSelection(
        const std::string &message,
        const Hand &currentHand) const;

    void removeCardsFromHand(
        Hand &currentHand,
        std::vector<size_t> indices) const;

    bool resolvePlayedHand(
        const Hand &playedHand,
        ScoringRule &scoringRule,
        BlindRule &blindRule,
        RewardRule &rewardRule,
        JokerManager &jokerManager);

    void drawToHand(
        Hand &currentHand,
        std::vector<Card> &deck,
        size_t targetCount) const;
};