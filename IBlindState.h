#pragma once

// Forward declaration to avoid circular dependency
class BlindManager;

/**
 * Abstract interface for blind progression states.
 *
 * Encapsulates blind-specific behavior including:
 * - Score requirements to pass the blind
 * - Rewards for passing
 * - Progression logic (determining next state)
 * - Special ante progression behavior
 */
class IBlindState
{
public:
    virtual ~IBlindState() = default;

    /**
     * Get the required score to pass this blind.
     * For standard blinds, this is fixed.
     * For ante-based blinds, this may vary with ante.
     *
     * @return The score threshold needed to advance
     */
    virtual int getRequiredScore() const = 0;

    /**
     * Get the reward (chips/money) for passing this blind.
     *
     * @return The reward value for passing
     */
    virtual int getReward() const = 0;

    /**
     * Get a human-readable name for this blind stage.
     *
     * @return String describing the blind type
     */
    virtual const char *getName() const = 0;

    /**
     * Determine and transition to the next blind state.
     *
     * This method encapsulates progression logic:
     * - Standard blinds cycle: Small → Big → Boss → Ante
     * - Ante progression: Increments ante and returns to Small
     * - Some states may trigger special behaviors
     *
     * @param manager The blind manager to request state transitions
     * @param blindWon Whether the player passed the current blind
     */
    virtual void transitionToNextState(
        BlindManager &manager,
        bool blindWon) = 0;
};
