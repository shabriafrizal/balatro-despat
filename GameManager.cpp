#include <iostream>
#include <memory>

#include "GameManager.h"
#include "Jokers/FlatChipJoker.h"
#include "HandRankUtils.h"
#include "Jokers/PairJoker.h"
#include "ScoreContext.h"

void GameManager::setupJokers()
{
    jokerManager.clear();
    jokerManager.addJoker(std::make_unique<PairJoker>());
    jokerManager.addJoker(std::make_unique<FlatChipJoker>());
}

void GameManager::runSession()
{
    std::cout << "=== Run Started ===\n";
    setupJokers();

    // Generate initial hand with 5 cards
    Hand generatedHand = handGenerator.generateHand(5);
    std::cout << "[Debug] Generated hand with " << generatedHand.getCardCount() << " cards\n";

    // Get user input to choose cards
    Hand selectedHand = chooseHand.chooseFromHandWithUserInput(generatedHand);
    std::cout << "[Debug] Selected hand with " << selectedHand.getCardCount() << " cards\n";

    BaseScore baseScore = scoringRule.calculateBaseScore(selectedHand);

    ScoreContext scoreContext;
    scoreContext.hand = &selectedHand;
    scoreContext.handType = baseScore.handType;
    scoreContext.chips = baseScore.chips;
    scoreContext.multiplier = baseScore.multiplier;
    scoreContext.recomputeFinalScore();

    jokerManager.applyJokers(scoreContext);

    std::cout << "Hand type: " << handRankToString(scoreContext.handType) << "\n";
    std::cout << "Chips: " << scoreContext.chips << " | Mult: " << scoreContext.multiplier << "\n";
    std::cout << "Final score: " << scoreContext.finalScore << "\n";

    bool win = blindRule.checkBlind(scoreContext.finalScore);
    int reward = rewardRule.earnMoney(win, scoreContext.finalScore);
    std::cout << "[Debug] Money gained: " << reward << "\n";
    std::cout << "=== Run Ended ===\n";
}