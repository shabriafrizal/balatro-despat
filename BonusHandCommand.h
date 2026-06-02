#pragma once

#include "RewardCommand.h"

/**
 * Reward command that grants an additional hand/play.
 *
 * When executed, this command increments the remaining hands available
 * in the current blind, allowing the player to use one more hand.
 *
 * Typical timing: Immediate or NextBlind
 */
class BonusHandCommand : public RewardCommand
{
public:
    const char *getName() const override;
    const char *getDescription() const override;
    void execute(RunSessionState &state) override;

private:
    static constexpr int HAND_BONUS = 1;
};
