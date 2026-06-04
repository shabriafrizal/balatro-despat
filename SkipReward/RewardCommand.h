#pragma once

#include "RunSessionState.h"

namespace SkipReward
{

    /**
     * Abstract base for all skip-reward commands.
     * Each concrete command encapsulates a single reward effect
     * (e.g. +1 hand, +$25, free reroll).
     */
    class RewardCommand
    {
    public:
        virtual ~RewardCommand() = default;

        /** Human-readable name (e.g. "Bonus Hand") */
        virtual const char *getName() const = 0;

        /** Human-readable description (e.g. "Gain +1 hand next blind") */
        virtual const char *getDescription() const = 0;

        /** Apply the reward effect to the given session state */
        virtual void execute(RunSessionState &state) = 0;
    };

} // namespace SkipReward
