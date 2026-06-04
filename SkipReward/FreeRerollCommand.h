#pragma once

#include "RewardCommand.h"

namespace SkipReward
{

    class FreeRerollCommand : public RewardCommand
    {
    public:
        const char *getName() const override { return "Free Reroll"; }
        const char *getDescription() const override { return "Gain 1 free shop reroll"; }

        void execute(RunSessionState &state) override
        {
            state.freeRerolls += 1;
        }
    };

} // namespace SkipReward
