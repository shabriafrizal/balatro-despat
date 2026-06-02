#include "RewardCommandQueue.h"
#include "RunSessionState.h"

#include <algorithm>

void RewardCommandQueue::enqueue(CommandTiming timing, std::unique_ptr<RewardCommand> command)
{
    // TODO: Implement
    // - Create PendingCommand with timing and command
    // - Add to queue vector
}

void RewardCommandQueue::executeCommandsWithTiming(CommandTiming timing, RunSessionState &state)
{
    // TODO: Implement
    // - Iterate through queue
    // - Find all pending commands matching timing
    // - Execute each command: command->execute(state)
    // - Mark command as executed: pending.executed = true
    // - Consider logging: "Executed [CommandName]"
}

size_t RewardCommandQueue::getPendingCommandCount() const
{
    // TODO: Implement
    // - Count all commands where executed == false
    // - Return count
    return 0;
}

const std::vector<PendingCommand> &RewardCommandQueue::getPendingCommands() const
{
    // TODO: Implement
    // - Filter queue to return only unexecuted commands
    // - Or: return reference to queue and let caller filter
    // - Decision: Modify return type or add filtering in caller?
    return queue;
}

void RewardCommandQueue::clearAll()
{
    // TODO: Implement
    // - queue.clear()
    // - Optional: Log how many commands were cleared
}
