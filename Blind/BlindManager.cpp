#include "BlindManager.h"
#include "IBlindState.h"
#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "BossBlindState.h"

#include "SkipReward/RewardCommandQueue.h"

#include <iostream>
#include <cassert>

void BlindManager::initializeProgression()
{
    ante = 1;
    currentState = std::make_unique<SmallBlindState>(ante);
    std::cout << "[Blind] Starting ante " << ante
              << " " << getCurrentBlindName()
              << " (required: " << getRequiredScore() << ")\n";
}

int BlindManager::getRequiredScore() const
{
    if (currentState)
    {
        return currentState->getRequiredScore();
    }
    return 0;
}

int BlindManager::getReward() const
{
    if (currentState)
    {
        return currentState->getReward();
    }
    return 0;
}

const char *BlindManager::getCurrentBlindName() const
{
    if (currentState)
    {
        return currentState->getName();
    }
    return "Unknown";
}

int BlindManager::getAnteLevel() const
{
    return ante;
}

bool BlindManager::canSkipCurrentBlind() const
{
    if (currentState)
    {
        return currentState->canSkip();
    }
    return false;
}

void BlindManager::skipBlind()
{
    if (!canSkipCurrentBlind())
    {
        std::cout << "[Blind] Cannot skip this blind!\n";
        return;
    }

    std::cout << "[Blind] Skipping " << getCurrentBlindName() << "...\n";
    // Advance as if won, but forfeit the reward
    if (currentState)
    {
        currentState->transitionToNextState(*this, true);
    }
}

void BlindManager::advanceBlind(bool blindWon)
{
    if (currentState)
    {
        currentState->transitionToNextState(*this, blindWon);
    }
}

void BlindManager::transitionToState(std::unique_ptr<IBlindState> newState)
{
    currentState = std::move(newState);
    std::cout << "[Blind] Now at ante " << ante
              << " " << getCurrentBlindName()
              << " (required: " << getRequiredScore() << ")\n";
}

void BlindManager::incrementAnte()
{
    ante++;
    std::cout << "[Blind] Ante increased to " << ante << "!\n";
}

void BlindManager::queueSkipRewards(SkipReward::RewardCommandQueue &queue)
{
    if (currentState)
    {
        currentState->queueSkipRewards(queue);
    }
}
