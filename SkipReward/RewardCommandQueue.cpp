#include "RewardCommandQueue.h"

namespace SkipReward
{

    void RewardCommandQueue::enqueue(CommandTiming timing, std::unique_ptr<RewardCommand> command)
    {
        PendingCommand pending;
        pending.timing = timing;
        pending.executed = false;
        pending.command = std::move(command);
        commands.push_back(std::move(pending));
    }

    void RewardCommandQueue::executeCommandsWithTiming(CommandTiming timing, RunSessionState &state)
    {
        for (auto &pending : commands)
        {
            if (!pending.executed && pending.timing == timing)
            {
                pending.command->execute(state);
                pending.executed = true;
            }
        }
    }

    size_t RewardCommandQueue::getPendingCommandCount() const
    {
        size_t count = 0;
        for (const auto &pending : commands)
        {
            if (!pending.executed)
                ++count;
        }
        return count;
    }

    const std::vector<PendingCommand> &RewardCommandQueue::getPendingCommands() const
    {
        return commands;
    }

    void RewardCommandQueue::clearAll()
    {
        commands.clear();
    }

} // namespace SkipReward
