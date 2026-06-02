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
    explicit SmallBlindState(int anteLevel);

    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    bool canSkip() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;

private:
    int ante;

    static constexpr int BASE_SCORE = 300;
    static constexpr int REWARD = 25;
};
