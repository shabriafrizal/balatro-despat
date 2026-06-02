#pragma once

/**
 * Runtime game state for a session/run.
 *
 * Represents mutable state that reward commands can modify.
 * This is separate from the blind progression state, focusing on
 * the immediate gameplay loop variables (hands, discards, money, etc.).
 *
 * This struct is passed to RewardCommand::execute() to allow commands
 * to apply their effects to the current run.
 *
 * TODO: Determine if this should merge with GameManager's state
 *       or remain as a separate, command-specific view of the state.
 */
struct RunSessionState
{
    /**
     * Number of hands remaining this blind.
     * Bonus hand commands increment this.
     */
    int remainingPlays = 0;

    /**
     * Number of discards remaining this blind.
     * Bonus discard commands increment this.
     */
    int remainingDiscards = 0;

    /**
     * Number of free rerolls available.
     * Free reroll commands increment this.
     *
     * TODO: Define what "reroll" means in context (hand selection? deck manipulation?)
     */
    int freeRerolls = 0;

    /**
     * Current money/chips in the run.
     * Bonus money commands increment this.
     */
    int currentMoney = 0;

    /**
     * TODO: Add other state variables that commands may modify:
     *       - jokerSlots (for joker-granting commands)
     *       - consumableSlots (for consumable-granting commands)
     *       - currentHand reference?
     *       - Other progression metrics
     */
};
