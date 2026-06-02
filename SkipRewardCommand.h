#pragma once

/**
 * @file SkipRewardCommand.h
 *
 * Command Pattern — Skip Reward System
 *
 * When a player SKIPS a blind, a reward command is created and stored
 * in a queue. The command is executed LATER based on timing rules,
 * separating the decision to skip from the reward delivery.
 *
 * This decouples:
 *   - Gameplay flow (State Pattern: BlindManager/IBlindState)
 *   - Gameplay effects (Command Pattern: ISkipRewardCommand)
 *
 * Hierarchy:
 *   ISkipRewardCommand           (abstract command)
 *     ├── MoneySkipReward        (flat money bonus)
 *     ├── ChipBonusReward        (bonus chips for next blind)
 *     └── FreeShopReward         (one free shop visit)
 */

// ---------------------------------------------------------------------------
// Abstract Command
// ---------------------------------------------------------------------------

/**
 * Abstract base for all skip-reward commands.
 *
 * Each concrete command encapsulates:
 *   - What reward is granted
 *   - Which blind was skipped to earn it
 *   - When it should be executed (timing rule)
 */
class ISkipRewardCommand
{
public:
    virtual ~ISkipRewardCommand() = default;

    /**
     * Execute the reward, mutating the provided game state references.
     *
     * @param money   Reference to the player's money (mutated on execution)
     * @param chips   Reference to bonus chips for current blind (mutated)
     */
    virtual void execute(int &money, int &chips) = 0;

    /**
     * Human-readable description of what this reward will grant.
     * Displayed to the player when the reward is pending.
     */
    virtual const char *getDescription() const = 0;

    /**
     * Name of the blind that was skipped to earn this reward.
     */
    virtual const char *getBlindSource() const = 0;

    /**
     * Timing rule: when should this command be executed?
     *
     * @return true  → execute after the NEXT blind is completed
     *         false → execute after the current ante's BOSS blind
     */
    virtual bool executeAfterNextBlind() const = 0;
};

// ---------------------------------------------------------------------------
// Concrete Commands
// ---------------------------------------------------------------------------

/**
 * Command: Grants a flat money reward for skipping a blind.
 * Executes after the next blind is completed (immediate deferred reward).
 */
class MoneySkipReward : public ISkipRewardCommand
{
public:
    MoneySkipReward(int amount, const char *blindSource);

    void execute(int &money, int &chips) override;
    const char *getDescription() const override;
    const char *getBlindSource() const override;
    bool executeAfterNextBlind() const override;

private:
    int rewardAmount;
    const char *sourceBlind;
};

/**
 * Command: Grants bonus chips for the next blind after skipping.
 * Executes when the next blind starts (pre-battle reward).
 */
class ChipBonusReward : public ISkipRewardCommand
{
public:
    ChipBonusReward(int bonusChips, const char *blindSource);

    void execute(int &money, int &chips) override;
    const char *getDescription() const override;
    const char *getBlindSource() const override;
    bool executeAfterNextBlind() const override;

private:
    int chipBonus;
    const char *sourceBlind;
};

/**
 * Command: Grants one free shop visit (no cost to reroll/buy).
 * Executes after the current ante's Boss blind is defeated.
 */
class FreeShopReward : public ISkipRewardCommand
{
public:
    explicit FreeShopReward(const char *blindSource);

    void execute(int &money, int &chips) override;
    const char *getDescription() const override;
    const char *getBlindSource() const override;
    bool executeAfterNextBlind() const override;

private:
    const char *sourceBlind;
};
