#include "JokerManager.h"

void JokerManager::addJoker(std::unique_ptr<Joker> joker)
{
    if (joker)
    {
        jokers.push_back(std::move(joker));
    }
}

void JokerManager::clear()
{
    jokers.clear();
}

void JokerManager::applyJokers(ScoreContext &context)
{
    for (const auto &joker : jokers)
    {
        joker->onScoreCalculated(context);
    }

    context.recomputeFinalScore();
}

const std::vector<std::unique_ptr<Joker>> &JokerManager::getJokers() const
{
    return jokers;
}
