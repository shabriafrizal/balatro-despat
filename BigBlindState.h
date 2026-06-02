#pragma once

#include "IBlindState.h"

/**
 * Big Blind state in the blind progression cycle.
 *
 * Second blind stage with:
 * - Fixed score requirement (higher than Small Blind)
 * - Increased reward
 * - Transitions to BossBlindState on pass
 */
class BigBlindState : public IBlindState
{
public:
    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;

private:
    static constexpr int REQUIRED_SCORE = 200;
    static constexpr int REWARD = 50;
};
