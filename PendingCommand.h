#pragma once

#include <memory>
#include "CommandTiming.h"

class RewardCommand;

/**
 * Wraps a reward command with its execution timing and state tracking.
 *
 * Enables deferred execution of rewards by tracking:
 * - When the command should be executed (timing)
 * - Whether the command has already been executed
 * - The command itself
 *
 * Usage:
 *   auto pending = PendingCommand{
 *       CommandTiming::NextBlind,
 *       std::make_unique<BonusHandCommand>()
 *   };
 *
 *   if (shouldExecute(pending)) {
 *       pending.command->execute(state);
 *       pending.executed = true;
 *   }
 */
struct PendingCommand
{
    /**
     * When this command should be executed in the game flow.
     */
    CommandTiming timing = CommandTiming::Immediate;

    /**
     * Whether this command has already been executed.
     * Prevents accidental re-execution.
     */
    bool executed = false;

    /**
     * The reward command to execute.
     * Owns the command's lifetime.
     */
    std::unique_ptr<RewardCommand> command;

    /**
     * Constructor for convenient initialization.
     *
     * @param t The execution timing
     * @param cmd The command to execute (takes ownership)
     */
    PendingCommand(CommandTiming t, std::unique_ptr<RewardCommand> cmd)
        : timing(t), command(std::move(cmd))
    {
    }

    /**
     * Default constructor for containers.
     */
    PendingCommand() = default;
};
