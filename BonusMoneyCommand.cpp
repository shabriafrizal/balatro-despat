#include "BonusMoneyCommand.h"
#include "RunSessionState.h"

BonusMoneyCommand::BonusMoneyCommand(int amount)
    : bonusAmount(amount)
{
    // TODO: Implement - validate amount > 0
}

const char *BonusMoneyCommand::getName() const
{
    // TODO: Implement - return "Bonus Money"
    return nullptr;
}

const char *BonusMoneyCommand::getDescription() const
{
    // TODO: Implement - return formatted string like "+25 Money" using bonusAmount
    // Note: May need to return std::string instead for formatting
    return nullptr;
}

void BonusMoneyCommand::execute(RunSessionState &state)
{
    // TODO: Implement - state.currentMoney += bonusAmount
}
