#pragma once
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

    HandGenerator handGenerator;
    HandPlayer handPlayer;
    ScoringRule scoringRule;
    BlindRule blindRule;
    RewardRule rewardRule;
    ChooseHand chooseHand;
    JokerManager jokerManager;
};