#pragma once

#include <vector>

#include "Hand/HandGenerator.h"
#include "Hand/HandPlayer.h"
#include "Scoring/ScoringRule.h"
#include "Blind/BlindRule.h"
#include "Scoring/RewardRule.h"
#include "Hand/ChooseHand.h"
#include "Joker/JokerManager.h"
#include "Blind/BlindManager.h"
#include "Shop/Shop.h"
#include "SkipReward/RewardCommandQueue.h"

class GameManager
{
public:
    void runSession();

private:
    void setupJokers();
    void buildAndShuffleDeck();
    void drawToHand(size_t targetCount);
    void displayCurrentHand() const;

    /** Start a new blind: show info, reset hands/discards and accumulated score */
    void startBlind();

    /** Try to play a hand; returns true if the blind was cleared */
    bool tryPlayHand();

    /** Try to discard cards */
    void tryDiscard();

    /** Build RunSessionState snapshot and execute queued commands at a timing checkpoint */
    void executePendingCommands(SkipReward::CommandTiming timing);

private:
    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    ChooseHand chooseHand;
    JokerManager jokerManager;
    BlindManager blindManager;
    Shop shop;
    SkipReward::RewardCommandQueue commandQueue;

    Hand currentHand;
    std::vector<Card> deck;

    int handsRemaining = 4;
    int discardsRemaining = 3;
    int money = 0;
    int freeRerolls = 0;

    bool runWon = false;
};