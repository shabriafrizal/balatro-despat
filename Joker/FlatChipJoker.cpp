#include "FlatChipJoker.h"

std::string FlatChipJoker::getName() const
{
    return "Flat Chip Joker";
}

std::string FlatChipJoker::getDescription(const ScoreContext &context) const
{
    (void)context;
    return "Always: +20 chips";
}

int FlatChipJoker::getPrice() const
{
    return 4;
}

void FlatChipJoker::onScoreCalculated(ScoreContext &context)
{
    context.chips += 20;
}
