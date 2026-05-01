#pragma once
#include "../PokerHandChecker.h"

class FullHouseChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (PokerHandUtils::countRanksWithCount(analysis, 3) == 1 &&
            PokerHandUtils::countRanksWithCount(analysis, 2) == 1)
        {
            return HandRank::FULL_HOUSE;
        }
        return HandRank::NONE;
    }
};
