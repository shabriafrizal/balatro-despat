#pragma once

#include "HandRank.h"

struct HandScoreEntry
{
    int chips = 0;
    int multiplier = 1;
};

class HandScoreTable
{
public:
    HandScoreEntry getScore(HandRank handType) const;
};
