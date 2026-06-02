#include "BossBlindState.h"
#include "BlindManager.h"

int BossBlindState::getRequiredScore() const
{
    // TODO: Implement - return REQUIRED_SCORE
    return 0;
}

int BossBlindState::getReward() const
{
    // TODO: Implement - return REWARD
    return 0;
}

const char *BossBlindState::getName() const
{
    // TODO: Implement - return "Boss Blind"
    return nullptr;
}

void BossBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    // TODO: Implement
    // If blindWon, transition to AnteProgressionState
    // Otherwise, handle loss logic
}
