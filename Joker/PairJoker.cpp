#include "PairJoker.h"

std::string PairJoker::getName() const
{
    return "Pair Joker";
}

std::string PairJoker::getDescription(const ScoreContext &context) const
{
    if (context.handType == HandRank::PAIR)
    {
        return "Pair: +4 mult";
    }

    return "Pair: +4 mult";
}

int PairJoker::getPrice() const
{
    return 3;
}

void PairJoker::onScoreCalculated(ScoreContext &context)
{
    if (context.handType == HandRank::PAIR)
    {
        context.multiplier += 4;
    }
}
