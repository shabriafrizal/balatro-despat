#pragma once

#include <memory>
#include <vector>

#include "Joker.h"

/**
 * JokerManager acts as the Subject in the Observer Pattern.
 * It maintains a collection of Joker observers and notifies them
 * when a scoring event occurs.
 *
 *   Subject:  JokerManager  (attach / detach / notify)
 *   Observer: Joker         (IScoreObserver::onScoreCalculated)
 */
class JokerManager
{
public:
    /** Attach a Joker observer to be notified on scoring events */
    void attach(std::unique_ptr<Joker> observer);

    /** Remove all attached observers */
    void clear();

    /** Notify all attached observers of a scoring event */
    void notifyJokers(ScoreContext &context);

    /** Get read-only access to attached observers (for display) */
    const std::vector<std::unique_ptr<Joker>> &getJokers() const;

private:
    std::vector<std::unique_ptr<Joker>> observers;
};
