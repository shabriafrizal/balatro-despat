#pragma once

#include "RewardCommand.h"

/**
 * Reward command that grants bonus money/chips.
 *
 * When executed, this command adds money to the player's balance,
 * making funds available for purchasing items in shops.
 *
 * Configurable bonus amount via constructor.
 *
 * Typical timing: Immediate or NextShop
 */
class BonusMoneyCommand : public RewardCommand
{
public:
    /**
     * Constructor specifying the amount of money to grant.
     *
     * @param amount The money bonus to add (e.g., 10, 25, 50)
     */
    explicit BonusMoneyCommand(int amount);

    const char *getName() const override;
    const char *getDescription() const override;
    void execute(RunSessionState &state) override;

private:
    int bonusAmount;

    static constexpr int DEFAULT_BONUS = 25;
};
