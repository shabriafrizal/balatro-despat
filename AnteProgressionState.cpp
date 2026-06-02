#include "AnteProgressionState.h"
#include "BlindManager.h"

AnteProgressionState::AnteProgressionState(int currentAnte)
    : ante(currentAnte)
{
    // TODO: Implement - validate ante >= 0
}

int AnteProgressionState::getRequiredScore() const
{
    // TODO: Implement - return BASE_SCORE + (ante * SCORE_PER_ANTE)
    return 0;
}

int AnteProgressionState::getReward() const
{
    // TODO: Implement - return BASE_REWARD + (ante * REWARD_PER_ANTE)
    return 0;
}

const char *AnteProgressionState::getName() const
{
    // TODO: Implement - return formatted string like "Ante Progression (Ante 2)"
    // Note: May need to return std::string instead for formatting
    return nullptr;
}

void AnteProgressionState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    // TODO: Implement
    // If blindWon:
    //   - Increment ante in BlindManager
    //   - Transition to SmallBlindState to start new cycle
    // Otherwise:
    //   - Handle loss logic
}
