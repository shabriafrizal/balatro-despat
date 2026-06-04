#pragma once

#include "PendingCommand.h"
#include "CommandTiming.h"
#include "RunSessionState.h"

#include <vector>
#include <memory>

namespace SkipReward
{

    /**
     * Manages a queue of deferred skip-reward commands.
     *
     * Commands are enqueued with a timing hint and executed in batch
     * when the corresponding game-phase checkpoint is reached.
     */
    class RewardCommandQueue
    {
    public:
        /** Add a reward command to be executed at the given timing */
        void enqueue(CommandTiming timing, std::unique_ptr<RewardCommand> command);

        /** Execute all unexecuted commands whose timing matches */
        void executeCommandsWithTiming(CommandTiming timing, RunSessionState &state);

        /** Number of pending (unexecuted) commands */
        size_t getPendingCommandCount() const;

        /** List all pending commands (for UI preview) */
        const std::vector<PendingCommand> &getPendingCommands() const;

        /** Remove all queued commands */
        void clearAll();

    private:
        std::vector<PendingCommand> commands;
    };

} // namespace SkipReward
