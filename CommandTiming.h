#pragma once

/**
 * Timing enumeration for deferred reward command execution.
 *
 * Determines when a pending reward command should be activated
 * in relation to game progression events.
 */
enum class CommandTiming
{
    /**
     * Execute immediately when the reward is granted.
     * Used for rewards that take effect right away.
     */
    Immediate,

    /**
     * Execute at the start of the next blind.
     * Used for rewards that affect the next encounter.
     */
    NextBlind,

    /**
     * Execute at the next shop/reward selection screen.
     * Used for rewards that manifest during shopping phases.
     */
    NextShop,

    /**
     * Execute at the start of the next ante progression.
     * Used for long-term progression bonuses.
     */
    NextAnte
};
