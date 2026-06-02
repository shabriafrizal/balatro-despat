#pragma once

#include <vector>
#include "PendingCommand.h"
#include "CommandTiming.h"

struct RunSessionState;

/**
 * Manages a queue of pending reward commands with deferred execution.
 *
 * Enables:
 * - Collecting rewards without immediate execution
 * - Executing commands at appropriate game flow points
 * - Tracking which commands have been executed
 * - Querying pending rewards for UI display
 *
 * Usage:
 *   RewardCommandQueue queue;
 *   queue.enqueue(CommandTiming::NextBlind, std::make_unique<BonusHandCommand>());
 *
 *   // Later, at game checkpoints:
 *   queue.executeCommandsWithTiming(CommandTiming::NextBlind, state);
 */
class RewardCommandQueue
{
public:
    /**
     * Add a pending command to the queue.
     * The queue takes ownership of the command.
     *
     * @param timing When this command should execute
     * @param command The command to enqueue
     */
    void enqueue(CommandTiming timing, std::unique_ptr<RewardCommand> command);

    /**
     * Execute all pending commands matching the given timing.
     * Marks executed commands to prevent re-execution.
     *
     * @param timing The timing checkpoint to process
     * @param state The game state to pass to commands
     */
    void executeCommandsWithTiming(CommandTiming timing, RunSessionState &state);

    /**
     * Get the number of unexecuted commands in the queue.
     * Useful for UI to show "Pending Rewards" indicator.
     *
     * @return Count of pending (unexecuted) commands
     */
    size_t getPendingCommandCount() const;

    /**
     * Get all pending (unexecuted) commands.
     * Useful for UI to preview upcoming rewards.
     *
     * TODO: Decide return type - const reference? const copy? iterator?
     *
     * @return Vector of pending commands
     */
    const std::vector<PendingCommand> &getPendingCommands() const;

    /**
     * Clear all commands from the queue.
     * Called when starting a new run or when run ends.
     */
    void clearAll();

private:
    /**
     * All pending commands, executed or not.
     * Executed commands remain in the queue with executed=true
     * to preserve history (optional for debugging/UI).
     */
    std::vector<PendingCommand> queue;

    /**
     * TODO: Consider adding:
     *       - Command history for undo/redo
     *       - Execution callbacks for logging
     *       - Max queue size to prevent memory bloat
     */
};
