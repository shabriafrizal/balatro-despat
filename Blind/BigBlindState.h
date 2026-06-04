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
    explicit BigBlindState(int anteLevel);

    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    bool canSkip() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;
    void queueSkipRewards(SkipReward::RewardCommandQueue &queue) override;

private:
    int ante;

    static constexpr int BASE_SCORE = 450;
    static constexpr int REWARD = 50;
};
