#pragma once
#include "../PokerHandChecker.h"

class StraightChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (analysis.isStraight)
        {
            return HandRank::STRAIGHT;
        }
        return HandRank::NONE;
    }
};
