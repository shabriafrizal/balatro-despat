#include "Blind.h"

Blind::Blind()
    : currentState(BlindState::SMALL_BLIND), anteLevel(1)
{
}

Blind::Blind(BlindState state, int anteLevel)
    : currentState(state), anteLevel(anteLevel)
{
}

std::string Blind::getBlindName() const
{
    std::string name;
    switch (currentState)
    {
    case BlindState::SMALL_BLIND:
        name = "Small Blind";
        break;
    case BlindState::BIG_BLIND:
        name = "Big Blind";
        break;
    case BlindState::BOSS_BLIND:
        name = "Boss Blind";
        break;
    case BlindState::INCREASING_ANTE:
        name = "Ante " + std::to_string(anteLevel);
        break;
    }
    return name;
}

int Blind::getTargetScore() const
{
    return calculateTargetScore();
}

int Blind::getRewardMoney() const
{
    return calculateRewardMoney();
}

BlindState Blind::getCurrentState() const
{
    return currentState;
}

int Blind::getAnteLevel() const
{
    return anteLevel;
}

BlindState Blind::getNextState()
{
    return computeNextState();
}

bool Blind::canSkip() const
{
    // Only SMALL_BLIND and BIG_BLIND can be skipped
    return currentState == BlindState::SMALL_BLIND || currentState == BlindState::BIG_BLIND;
}

int Blind::getSkipReward() const
{
    if (!canSkip())
    {
        return 0;
    }
    // Skip reward is 1/2 of the normal reward
    return calculateRewardMoney() / 2;
}

void Blind::advanceToNextState()
{
    BlindState nextState = computeNextState();
    currentState = nextState;

    // Increment ante level when transitioning back to SMALL_BLIND
    if (nextState == BlindState::SMALL_BLIND && currentState != BlindState::SMALL_BLIND)
    {
        anteLevel++;
    }
}

int Blind::calculateTargetScore() const
{
    // Base scores per blind type
    const int SMALL_BLIND_BASE = 100;
    const int BIG_BLIND_BASE = 200;
    const int BOSS_BLIND_BASE = 400;
    const int ANTE_MULTIPLIER = 50;

    int baseScore = 0;
    switch (currentState)
    {
    case BlindState::SMALL_BLIND:
        baseScore = SMALL_BLIND_BASE;
        break;
    case BlindState::BIG_BLIND:
        baseScore = BIG_BLIND_BASE;
        break;
    case BlindState::BOSS_BLIND:
        baseScore = BOSS_BLIND_BASE;
        break;
    case BlindState::INCREASING_ANTE:
        baseScore = BOSS_BLIND_BASE + (anteLevel * ANTE_MULTIPLIER);
        break;
    }

    // Increase difficulty with each ante level (only applies to SMALL/BIG/BOSS)
    if (currentState != BlindState::INCREASING_ANTE)
    {
        baseScore += (anteLevel - 1) * 50;
    }

    return baseScore;
}

int Blind::calculateRewardMoney() const
{
    // Reward scaling
    const int SMALL_BLIND_REWARD = 25;
    const int BIG_BLIND_REWARD = 50;
    const int BOSS_BLIND_REWARD = 100;
    const int ANTE_REWARD_MULTIPLIER = 10;

    int baseReward = 0;
    switch (currentState)
    {
    case BlindState::SMALL_BLIND:
        baseReward = SMALL_BLIND_REWARD;
        break;
    case BlindState::BIG_BLIND:
        baseReward = BIG_BLIND_REWARD;
        break;
    case BlindState::BOSS_BLIND:
        baseReward = BOSS_BLIND_REWARD;
        break;
    case BlindState::INCREASING_ANTE:
        baseReward = BOSS_BLIND_REWARD + (anteLevel * ANTE_REWARD_MULTIPLIER);
        break;
    }

    // Increase reward with ante level
    if (currentState != BlindState::INCREASING_ANTE)
    {
        baseReward += (anteLevel - 1) * 10;
    }

    return baseReward;
}

BlindState Blind::computeNextState() const
{
    // Progression: SMALL -> BIG -> BOSS -> INCREASING_ANTE -> SMALL
    switch (currentState)
    {
    case BlindState::SMALL_BLIND:
        return BlindState::BIG_BLIND;
    case BlindState::BIG_BLIND:
        return BlindState::BOSS_BLIND;
    case BlindState::BOSS_BLIND:
        return BlindState::INCREASING_ANTE;
    case BlindState::INCREASING_ANTE:
        return BlindState::SMALL_BLIND;
    }
    return BlindState::SMALL_BLIND;
}
