#include <iostream>
#include "GameManager.h"
void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";
    Hand hand = handGenerator.generateHand();
    // TODO: Use a player-chosen hand when selection is implemented.
    // handPlayer.playHand();
    int score = scoringRule.scoreHand(hand);
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);
    std::cout << "Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}