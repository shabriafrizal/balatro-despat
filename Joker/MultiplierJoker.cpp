#include "MultiplierJoker.h"
#include "../Scoring/ScoreContext.h"

std::string MultiplierJoker::getName() const
{
    return "Multiplier Joker";
}

std::string MultiplierJoker::getDescription(const ScoreContext &context) const
{
    return "Doubles the multiplier (2x mult)";
}

void MultiplierJoker::onScoreCalculated(ScoreContext &context)
{
    context.multiplier *= 2;
}
