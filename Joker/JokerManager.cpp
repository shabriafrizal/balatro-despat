#include "JokerManager.h"

void JokerManager::attach(std::unique_ptr<Joker> observer)
{
    if (observer)
    {
        observers.push_back(std::move(observer));
    }
}

void JokerManager::clear()
{
    observers.clear();
}

void JokerManager::notifyJokers(ScoreContext &context)
{
    for (const auto &observer : observers)
    {
        observer->onScoreCalculated(context);
    }

    context.recomputeFinalScore();
}

const std::vector<std::unique_ptr<Joker>> &JokerManager::getJokers() const
{
    return observers;
}
