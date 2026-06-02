#pragma once

#include "../Hand/Hand.h"
#include "../Hand/HandRank.h"

struct BaseScore
{
    HandRank handType = HandRank::NONE;
    int chips = 0;
    int multiplier = 1;
};

class ScoringRule
{
public:
    BaseScore calculateBaseScore(const Hand &hand) const;
    int scoreHand(const Hand &hand) const;
};