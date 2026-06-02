#pragma once

#include "RewardCommand.h"

/**
 * Reward command that grants an additional discard.
 *
 * When executed, this command increments the remaining discards available
 * in the current blind, allowing the player to discard one more time.
 *
 * Typical timing: Immediate or NextBlind
 */
class BonusDiscardCommand : public RewardCommand
{
public:
    const char *getName() const override;
    const char *getDescription() const override;
    void execute(RunSessionState &state) override;

private:
    static constexpr int DISCARD_BONUS = 1;
};
