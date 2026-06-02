#pragma once

#include <vector>
#include <memory>

#include "SkipRewardCommand.h"

/**
 * SkipRewardQueue — stores deferred skip-reward commands.
 *
 * When a player skips a blind, the corresponding reward command
 * is enqueued here. Commands are executed later based on their
 * timing rules:
 *   - "After next blind" commands fire when the next blind ends
 *   - "After Boss" commands fire when the ante's Boss is defeated
 *
 * This is the Invoker side of the Command Pattern.
 */
class SkipRewardQueue
{
public:
    /**
     * Store a reward command for later execution.
     * Takes ownership of the command.
     */
    void enqueue(std::unique_ptr<ISkipRewardCommand> command);

    /**
     * Execute all commands whose timing rule is
     * executeAfterNextBlind() == true.
     *
     * @param money  Player money (mutated by money rewards)
     * @param chips  Bonus chips accumulator (mutated by chip rewards)
     * @return       Number of commands executed
     */
    int executeAfterNextBlindCommands(int &money, int &chips);

    /**
     * Execute all commands whose timing rule is
     * executeAfterNextBlind() == false (i.e., after Boss).
     *
     * @param money  Player money (mutated by money rewards)
     * @param chips  Bonus chips accumulator (mutated by chip rewards)
     * @return       Number of commands executed
     */
    int executeAfterBossCommands(int &money, int &chips);

    /**
     * Execute ALL pending commands regardless of timing rule.
     * Useful for end-of-run cleanup.
     */
    int executeAll(int &money, int &chips);

    /**
     * Whether the queue has any pending commands.
     */
    bool isEmpty() const;

    /**
     * Number of pending commands.
     */
    size_t size() const;

    /**
     * Print all pending commands to stdout.
     */
    void displayPending() const;

    /**
     * Remove all pending commands without executing them.
     */
    void clear();

private:
    std::vector<std::unique_ptr<ISkipRewardCommand>> commands;
};
