#pragma once

#include "RewardCommand.h"

/**
 * Reward command that grants a free reroll.
 *
 * When executed, this command increments the free reroll counter,
 * allowing the player to perform one additional reroll action
 * (behavior determined by game's reroll mechanism).
 *
 * Typical timing: Immediate or NextBlind
 *
 * TODO: Define reroll semantics:
 *       - Does it reroll the deck?
 *       - Does it reroll the current hand?
 *       - Can be used multiple times or one-time use?
 */
class FreeRerollCommand : public RewardCommand
{
public:
    const char *getName() const override;
    const char *getDescription() const override;
    void execute(RunSessionState &state) override;

private:
    static constexpr int REROLL_BONUS = 1;
};
