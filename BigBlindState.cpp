#include "BigBlindState.h"
#include "BlindManager.h"

int BigBlindState::getRequiredScore() const
{
    // TODO: Implement - return REQUIRED_SCORE
    return 0;
}

int BigBlindState::getReward() const
{
    // TODO: Implement - return REWARD
    return 0;
}

const char *BigBlindState::getName() const
{
    // TODO: Implement - return "Big Blind"
    return nullptr;
}

void BigBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    // TODO: Implement
    // If blindWon, transition to BossBlindState
    // Otherwise, handle loss logic
}
