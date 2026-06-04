#pragma once

#include "RewardCommand.h"
#include "CommandTiming.h"

#include <memory>

namespace SkipReward
{

    /**
     * Wraps a RewardCommand with its desired execution timing and
     * tracks whether it has already been executed.
     */
    struct PendingCommand
    {
        CommandTiming timing;
        bool executed = false;
        std::unique_ptr<RewardCommand> command;
    };

} // namespace SkipReward
