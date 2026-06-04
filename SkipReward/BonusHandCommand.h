#pragma once

#include "RewardCommand.h"

namespace SkipReward
{

    class BonusHandCommand : public RewardCommand
    {
    public:
        const char *getName() const override { return "Bonus Hand"; }
        const char *getDescription() const override { return "Gain +1 hand next blind"; }

        void execute(RunSessionState &state) override
        {
            state.remainingPlays += 1;
        }
    };

} // namespace SkipReward
