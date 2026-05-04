#include <iostream>
#include "GameManager.h"
void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";

    // Generate initial hand with 5 cards
    Hand generatedHand = handGenerator.generateHand(5);
    std::cout << "[Debug] Generated hand with " << generatedHand.getCardCount() << " cards\n";

    // Get user input to choose cards
    Hand selectedHand = chooseHand.chooseFromHandWithUserInput(generatedHand);
    std::cout << "[Debug] Selected hand with " << selectedHand.getCardCount() << " cards\n";

    int score = scoringRule.scoreHand(selectedHand);
    bool win = blindRule.checkBlind(score);
    int reward = rewardRule.earnMoney(win, score);
    std::cout << "[Debug] Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}