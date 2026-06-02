#pragma once

#include "IBlindState.h"

/**
 * Small Blind state in the blind progression cycle.
 *
 * First blind stage with:
 * - Fixed score requirement
 * - Base reward
 * - Transitions to BigBlindState on pass
 */
class SmallBlindState : public IBlindState
{
public:
    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;

private:
    static constexpr int REQUIRED_SCORE = 100;
    static constexpr int REWARD = 25;
};
