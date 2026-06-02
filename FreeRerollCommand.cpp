#include "FreeRerollCommand.h"
#include "RunSessionState.h"

const char *FreeRerollCommand::getName() const
{
    // TODO: Implement - return "Free Reroll"
    return nullptr;
}

const char *FreeRerollCommand::getDescription() const
{
    // TODO: Implement - return "Gain 1 free reroll."
    return nullptr;
}

void FreeRerollCommand::execute(RunSessionState &state)
{
    // TODO: Implement - state.freeRerolls += REROLL_BONUS
}
