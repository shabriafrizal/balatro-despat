#pragma once

#include <memory>

#include "IBlindState.h"

/**
 * Manages blind progression state and transitions.
 *
 * This service is responsible for:
 * - Owning the current blind state
 * - Tracking ante progression
 * - Determining when to advance to the next state
 * - Querying current blind requirements and rewards
 *
 * Usage:
 *   BlindManager blindManager;
 *   while (gameRunning) {
 *       int requiredScore = blindManager.getRequiredScore();
 *       bool playerPassed = checkScore(requiredScore);
 *       int reward = blindManager.getReward();
 *       blindManager.advanceBlind(playerPassed);
 *   }
 */
class BlindManager
{
public:
    /**
     * Initialize blind progression at the start of a run.
     * Sets initial state to SmallBlindState with ante = 1.
     */
    void initializeProgression();

    /**
     * Get the current required score to pass the blind.
     * Delegates to the current state.
     *
     * @return Score threshold for current blind
     */
    int getRequiredScore() const;

    /**
     * Get the reward for passing the current blind.
     * Delegates to the current state.
     *
     * @return Reward value for current blind
     */
    int getReward() const;

    /**
     * Get the name of the current blind stage.
     * Delegates to the current state.
     *
     * @return Human-readable blind name
     */
    const char *getCurrentBlindName() const;

    /**
     * Get the current ante level.
     * Used by blind states to scale requirements.
     *
     * @return Current ante value
     */
    int getAnteLevel() const;

    /**
     * Whether the current blind can be skipped by the player.
     * Boss Blinds cannot be skipped.
     *
     * @return true if the current blind allows skipping
     */
    bool canSkipCurrentBlind() const;

    /**
     * Skip the current blind, advancing to the next state
     * as if the blind was won (but with no reward).
     * Has no effect if the current blind cannot be skipped.
     */
    void skipBlind();

    /**
     * Advance blind progression to the next state.
     * The current state determines what comes next.
     *
     * @param blindWon Whether the player passed the current blind
     */
    void advanceBlind(bool blindWon);

    /**
     * Request a state transition from a state object.
     * Internal method called by state objects during transitionToNextState().
     *
     * @param newState The new state to transition to (takes ownership)
     */
    void transitionToState(std::unique_ptr<IBlindState> newState);

    /**
     * Increment ante counter.
     * Called after passing BossBlindState.
     * This increases difficulty for the next cycle of blinds.
     */
    void incrementAnte();

private:
    std::unique_ptr<IBlindState> currentState;
    int ante = 1;

    // TODO: Add helper method to create initial state objects
    // TODO: Consider adding runEnded flag or callback for run completion
};
