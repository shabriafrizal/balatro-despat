#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "BlindManager.h"

SmallBlindState::SmallBlindState(int anteLevel)
    : ante(anteLevel)
{
}

int SmallBlindState::getRequiredScore() const
{
    return BASE_SCORE * ante;
}

int SmallBlindState::getReward() const
{
    return REWARD * ante;
}

const char *SmallBlindState::getName() const
{
    return "Small Blind";
}

bool SmallBlindState::canSkip() const
{
    return true;
}

void SmallBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    if (blindWon)
    {
        manager.transitionToState(
            std::make_unique<BigBlindState>(manager.getAnteLevel()));
    }
    // If not won, the run is over — handled by GameManager
}
