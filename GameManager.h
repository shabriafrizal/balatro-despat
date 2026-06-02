#pragma once

#include <vector>

#include "HandGenerator.h"
#include "HandPlayer.h"
#include "ScoringRule.h"
#include "BlindRule.h"
#include "RewardRule.h"
#include "ChooseHand.h"
#include "JokerManager.h"

class GameManager
{
public:
    void runSession();

private:
    void setupJokers();
    void buildAndShuffleDeck();
    void drawToHand(size_t targetCount);
    void displayCurrentHand() const;

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    ChooseHand chooseHand;
    JokerManager jokerManager;

    Hand currentHand;
    std::vector<Card> deck;

    int handsRemaining = 4;
    int discardsRemaining = 3;

    bool runWon = false;
};