#pragma once

#include "IBlindState.h"

/**
 * Boss Blind state in the blind progression cycle.
 *
 * Third blind stage with:
 * - Fixed score requirement (highest in base cycle)
 * - Significant reward
 * - Transitions to AnteProgressionState on pass
 * - Potentially triggers special boss effects (placeholder for future)
 */
class BossBlindState : public IBlindState
{
public:
    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;

private:
    static constexpr int REQUIRED_SCORE = 400;
    static constexpr int REWARD = 100;
};
