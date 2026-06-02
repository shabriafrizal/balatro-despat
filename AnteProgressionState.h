#pragma once

#include "IBlindState.h"

/**
 * Ante Progression state in the blind progression cycle.
 *
 * Special state that:
 * - Scales score requirement with ante multiplier: 400 + (ante × 50)
 * - Scales reward with ante multiplier: 100 + (ante × 10)
 * - Increments ante counter when passed
 * - Returns to SmallBlindState after passing (starting new cycle)
 *
 * This state enables progressive difficulty as the run advances.
 */
class AnteProgressionState : public IBlindState
{
public:
    /**
     * Constructor accepting current ante value.
     * Ante is tracked externally in BlindManager.
     *
     * @param currentAnte The current ante level
     */
    explicit AnteProgressionState(int currentAnte);

    int getRequiredScore() const override;
    int getReward() const override;
    const char *getName() const override;
    void transitionToNextState(BlindManager &manager, bool blindWon) override;

private:
    int ante;

    static constexpr int BASE_SCORE = 400;
    static constexpr int SCORE_PER_ANTE = 50;
    static constexpr int BASE_REWARD = 100;
    static constexpr int REWARD_PER_ANTE = 10;
};
