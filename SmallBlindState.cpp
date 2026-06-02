#include "SmallBlindState.h"
#include "BlindManager.h"

int SmallBlindState::getRequiredScore() const
{
    // TODO: Implement - return REQUIRED_SCORE
    return 0;
}

int SmallBlindState::getReward() const
{
    // TODO: Implement - return REWARD
    return 0;
}

const char *SmallBlindState::getName() const
{
    // TODO: Implement - return "Small Blind"
    return nullptr;
}

void SmallBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    // TODO: Implement
    // If blindWon, transition to BigBlindState
    // Otherwise, handle loss logic (e.g., end run or reset)
}
