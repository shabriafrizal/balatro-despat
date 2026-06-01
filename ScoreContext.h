#pragma once

#include "Hand.h"
#include "HandRank.h"

struct ScoreContext
{
    const Hand *hand = nullptr;
    HandRank handType = HandRank::NONE;
    int level = 1;
    int chips = 0;
    int multiplier = 1;
    int finalScore = 0;

    void recomputeFinalScore()
    {
        finalScore = chips * multiplier;
    }
};
