#pragma once

#include "Joker.h"

/**
 * Multiplier Joker: Doubles the multiplier
 * 2x mult modifier
 */
class MultiplierJoker : public Joker
{
public:
    std::string getName() const override;
    std::string getDescription(const ScoreContext &context) const override;
    void onScoreCalculated(ScoreContext &context) override;
};
