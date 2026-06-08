#include "BigBlindState.h"
#include "BossBlindState.h"
#include "BlindManager.h"

#include "SkipReward/RewardCommandQueue.h"
#include "SkipReward/BonusMoneyCommand.h"
#include "SkipReward/BonusHandCommand.h"

BigBlindState::BigBlindState(int anteLevel)
    : ante(anteLevel)
{
}

int BigBlindState::getRequiredScore() const
{
    return BASE_SCORE * ante;
}

int BigBlindState::getReward() const
{
    return REWARD * ante;
}

const char *BigBlindState::getName() const
{
    return "Big Blind";
}

bool BigBlindState::canSkip() const
{
    return true;
}

void BigBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    if (blindWon)
    {
        manager.transitionToState(
            std::make_unique<BossBlindState>(manager.getAnteLevel()));
    }
}

void BigBlindState::queueSkipRewards(SkipReward::RewardCommandQueue &queue)
{
    // Big Blind skip: +1 hand next blind
    queue.enqueue(SkipReward::CommandTiming::NextBlind,
                  std::make_unique<SkipReward::BonusHandCommand>());
}
