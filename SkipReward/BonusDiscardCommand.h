#pragma once

#include "RewardCommand.h"

namespace SkipReward
{

    class BonusDiscardCommand : public RewardCommand
    {
    public:
        const char *getName() const override { return "Bonus Discard"; }
        const char *getDescription() const override { return "Gain +1 discard next blind"; }

        void execute(RunSessionState &state) override
        {
            state.remainingDiscards += 1;
        }
    };

} // namespace SkipReward
