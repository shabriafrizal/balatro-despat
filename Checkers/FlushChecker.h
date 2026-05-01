#pragma once
#include "../PokerHandChecker.h"

class FlushChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (analysis.isFlush)
        {
            return HandRank::FLUSH;
        }
        return HandRank::NONE;
    }
};
