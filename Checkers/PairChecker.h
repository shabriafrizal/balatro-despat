#pragma once
#include "../PokerHandChecker.h"

class PairChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (PokerHandUtils::countRanksWithCount(analysis, 2) == 1)
        {
            return HandRank::PAIR;
        }
        return HandRank::NONE;
    }
};
