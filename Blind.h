#pragma once

#include <string>
#include "BlindState.h"

class Blind
{
public:
    Blind();
    Blind(BlindState state, int anteLevel = 1);

    // Properties
    std::string getBlindName() const;
    int getTargetScore() const;
    int getRewardMoney() const;
    BlindState getCurrentState() const;
    int getAnteLevel() const;

    // Progression logic
    BlindState getNextState();

    // Skip reward system
    bool canSkip() const;
    int getSkipReward() const;

    // State transitions
    void advanceToNextState();

private:
    BlindState currentState;
    int anteLevel;

    // Helper methods
    int calculateTargetScore() const;
    int calculateRewardMoney() const;
    BlindState computeNextState() const;
};
