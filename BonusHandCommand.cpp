#include "BonusHandCommand.h"
#include "RunSessionState.h"

const char *BonusHandCommand::getName() const
{
    // TODO: Implement - return "Bonus Hand"
    return nullptr;
}

const char *BonusHandCommand::getDescription() const
{
    // TODO: Implement - return "Gain +1 hand next blind."
    return nullptr;
}

void BonusHandCommand::execute(RunSessionState &state)
{
    // TODO: Implement - state.remainingPlays += HAND_BONUS
}
