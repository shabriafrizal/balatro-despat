#include "BossBlindState.h"
#include "SmallBlindState.h"
#include "BlindManager.h"

#include "SkipReward/RewardCommandQueue.h"

BossBlindState::BossBlindState(int anteLevel)
    : ante(anteLevel)
{
}

int BossBlindState::getRequiredScore() const
{
    return BASE_SCORE * ante;
}

int BossBlindState::getReward() const
{
    return REWARD * ante;
}

const char *BossBlindState::getName() const
{
    return "Boss Blind";
}

bool BossBlindState::canSkip() const
{
    return false; // Boss Blinds cannot be skipped
}

void BossBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    if (blindWon)
    {
        // Increment ante for the next cycle
        manager.incrementAnte();
        // Start a new cycle at Small Blind with the new higher ante
        manager.transitionToState(
            std::make_unique<SmallBlindState>(manager.getAnteLevel()));
    }
}

void BossBlindState::queueSkipRewards(SkipReward::RewardCommandQueue & /*queue*/)
{
    // Boss Blinds cannot be skipped — this is never called
}
