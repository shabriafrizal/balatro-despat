#pragma once

#include <string>

#include "../Scoring/IScoreObserver.h"

/**
 * Joker is an Observer in the Observer Pattern.
 * It implements IScoreObserver::onScoreCalculated() to react to scoring events,
 * and adds joker-specific query methods (name, description, price).
 */
class Joker : public IScoreObserver
{
public:
    virtual ~Joker() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription(const ScoreContext &context) const = 0;
    virtual int getPrice() const = 0;
    // onScoreCalculated() is inherited from IScoreObserver
};
