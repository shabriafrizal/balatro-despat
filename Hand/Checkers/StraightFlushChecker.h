#pragma once
#include "../PokerHandChecker.h"

class StraightFlushChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (analysis.isFlush && analysis.isStraight)
        {
            return HandRank::STRAIGHT_FLUSH;
        }
        return HandRank::NONE;
    }
};
