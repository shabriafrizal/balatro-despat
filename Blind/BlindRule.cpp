#include <iostream>
#include "BlindRule.h"

void BlindRule::setRequiredScore(int score)
{
    requiredScore = score;
}

int BlindRule::getRequiredScore() const
{
    return requiredScore;
}

void BlindRule::addScore(int score)
{
    accumulatedScore += score;
}

int BlindRule::getAccumulatedScore() const
{
    return accumulatedScore;
}

bool BlindRule::isBlindCleared() const
{
    return accumulatedScore >= requiredScore;
}

void BlindRule::reset()
{
    requiredScore = 0;
    accumulatedScore = 0;
}