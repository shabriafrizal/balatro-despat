#pragma once
#include "../PokerHandChecker.h"

class TwoPairChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (PokerHandUtils::countRanksWithCount(analysis, 2) == 2)
        {
            return HandRank::TWO_PAIR;
        }
        return HandRank::NONE;
    }
};
