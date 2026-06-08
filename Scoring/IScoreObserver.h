#pragma once

#include "ScoreContext.h"

/**
 * Observer interface for the Observer Pattern.
 * Jokers (and potentially other scoring modifiers) implement this
 * to be notified when a hand score is calculated.
 */
class IScoreObserver
{
public:
    virtual ~IScoreObserver() = default;

    /**
     * Called by the Subject (JokerManager) when a hand is scored.
     * Each observer modifies the ScoreContext to apply its effect.
     */
    virtual void onScoreCalculated(ScoreContext &context) = 0;
};
