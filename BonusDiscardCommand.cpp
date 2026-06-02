#include "BonusDiscardCommand.h"
#include "RunSessionState.h"

const char *BonusDiscardCommand::getName() const
{
    // TODO: Implement - return "Bonus Discard"
    return nullptr;
}

const char *BonusDiscardCommand::getDescription() const
{
    // TODO: Implement - return "Gain +1 discard next blind."
    return nullptr;
}

void BonusDiscardCommand::execute(RunSessionState &state)
{
    // TODO: Implement - state.remainingDiscards += DISCARD_BONUS
}
