#pragma once

#include "IBlindState.h"

/**
 * Boss Blind state in the blind progression cycle.
 *
 * Third blind stage with:
 * - Score requirement scales with ante: 600 × ante
 * - Significant reward
 * - Increments ante and transitions to SmallBlindState on pass
 * - Potentially triggers special boss effects (placeholder for future)
 */
class BossBlindState : public IBlindState
{
public:
    explicit BossBlindState(int anteLevel);

    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    bool canSkip() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;
    void queueSkipRewards(SkipReward::RewardCommandQueue &queue) override;

private:
    int ante;

    static constexpr int BASE_SCORE = 600;
    static constexpr int REWARD = 100;
};
