#include "AnteProgressionState.h"
#include "../Blind/SmallBlindState.h"
#include "../Blind/BlindManager.h"

AnteProgressionState::AnteProgressionState(int currentAnte)
    : ante(currentAnte)
{
}

int AnteProgressionState::getRequiredScore() const
{
    return BASE_SCORE + (ante * SCORE_PER_ANTE);
}

int AnteProgressionState::getReward() const
{
    return BASE_REWARD + (ante * REWARD_PER_ANTE);
}

const char *AnteProgressionState::getName() const
{
    // Return a static string; the ante info is shown by the blind name.
    return "Ante Progression";
}

void AnteProgressionState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    if (blindWon)
    {
        // Increment ante for next cycle
        manager.incrementAnte();
        // Start a new cycle at Small Blind with higher ante
        manager.transitionToState(
            std::make_unique<SmallBlindState>(manager.getAnteLevel()));
    }
}
