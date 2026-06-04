#pragma once

#include "RewardCommand.h"

#include <string>

namespace SkipReward
{

    class BonusMoneyCommand : public RewardCommand
    {
    public:
        explicit BonusMoneyCommand(int amount) : bonusAmount(amount) {}

        const char *getName() const override { return "Bonus Money"; }

        const char *getDescription() const override
        {
            // Reuse a static buffer for the description string
            static char buf[64];
            snprintf(buf, sizeof(buf), "+$%d", bonusAmount);
            return buf;
        }

        void execute(RunSessionState &state) override
        {
            state.currentMoney += bonusAmount;
        }

    private:
        int bonusAmount;
    };

} // namespace SkipReward
