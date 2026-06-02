#include "BlindManager.h"
#include "IBlindState.h"
#include "SmallBlindState.h"
#include "BigBlindState.h"
#include "BossBlindState.h"
#include "AnteProgressionState.h"

#include <iostream>

void BlindManager::initializeProgression()
{
    // TODO: Implement
    // - Create initial SmallBlindState
    // - Set ante to 1
    // - Store in currentState
}

int BlindManager::getRequiredScore() const
{
    // TODO: Implement
    // - Return currentState->getRequiredScore() if currentState exists
    // - Return 0 or throw if no state (error handling)
    return 0;
}

int BlindManager::getReward() const
{
    // TODO: Implement
    // - Return currentState->getReward() if currentState exists
    // - Return 0 or throw if no state (error handling)
    return 0;
}

const char *BlindManager::getCurrentBlindName() const
{
    // TODO: Implement
    // - Return currentState->getName() if currentState exists
    // - Return "Unknown" or throw if no state (error handling)
    return nullptr;
}

int BlindManager::getAnteLevel() const
{
    // TODO: Implement - return ante
    return 0;
}

void BlindManager::advanceBlind(bool blindWon)
{
    // TODO: Implement
    // - Verify currentState exists
    // - Call currentState->transitionToNextState(*this, blindWon)
    // - This will trigger state's own transitionToState() call on this manager
}

void BlindManager::transitionToState(std::unique_ptr<IBlindState> newState)
{
    // TODO: Implement
    // - Update currentState with newState
    // - Optional: Log transition for debugging
}

void BlindManager::incrementAnte()
{
    // TODO: Implement
    // - Increment ante
    // - Optional: Log ante increase
    // - Consider max ante limits
}
