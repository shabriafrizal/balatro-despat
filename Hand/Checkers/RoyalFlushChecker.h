#pragma once
#include "../PokerHandChecker.h"

class RoyalFlushChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (analysis.isFlush && analysis.isStraight &&
            PokerHandUtils::hasRanks(analysis, {10, 11, 12, 13, 14}))
        {
            return HandRank::ROYAL_FLUSH;
        }
        return HandRank::NONE;
    }
};
