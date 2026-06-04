#include "MultiplierJoker.h"
#include "../Scoring/ScoreContext.h"

std::string MultiplierJoker::getName() const
{
    return "Multiplier Joker";
}

std::string MultiplierJoker::getDescription(const ScoreContext &context) const
{
    (void)context;
    return "Doubles the multiplier (2x mult)";
}

int MultiplierJoker::getPrice() const
{
    return 6;
}

void MultiplierJoker::onScoreCalculated(ScoreContext &context)
{
    context.multiplier *= 2;
}
