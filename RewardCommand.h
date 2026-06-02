#pragma once

// Forward declaration to avoid circular dependency
struct RunSessionState;

/**
 * Abstract interface for reward commands.
 *
 * Commands encapsulate the logic for different reward types that can be
 * granted when skipping blinds. Each command knows:
 * - Its name and description
 * - How to execute its effect on the game state
 *
 * This enables:
 * - Different reward logic without switch statements
 * - Deferred execution (commands can be stored and executed later)
 * - New reward types without modifying existing code
 * - Serialization and queueing of rewards
 */
class RewardCommand
{
public:
    virtual ~RewardCommand() = default;

    /**
     * Get the display name of this reward command.
     *
     * @return Human-readable name (e.g., "Bonus Hand")
     */
    virtual const char *getName() const = 0;

    /**
     * Get a detailed description of this reward's effect.
     *
     * @return Formatted description for UI display
     */
    virtual const char *getDescription() const = 0;

    /**
     * Execute this command's effect on the game state.
     *
     * Modifies the provided RunSessionState to apply the reward.
     * This method should be idempotent if it may be called multiple times,
     * or the caller should ensure single execution via pending command tracking.
     *
     * @param state The current session state to modify
     */
    virtual void execute(RunSessionState &state) = 0;
};
