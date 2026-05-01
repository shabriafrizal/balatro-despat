#pragma once
#include "../PokerHandChecker.h"

class ThreeOfAKindChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (PokerHandUtils::hasNOfKind(analysis, 3) &&
            PokerHandUtils::countRanksWithCount(analysis, 2) == 0)
        {
            return HandRank::THREE_OF_A_KIND;
        }
        return HandRank::NONE;
    }
};
