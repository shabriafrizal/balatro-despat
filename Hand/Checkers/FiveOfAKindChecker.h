#pragma once
#include "../PokerHandChecker.h"

class FiveOfAKindChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (PokerHandUtils::hasNOfKind(analysis, 5))
        {
            return HandRank::FIVE_OF_A_KIND;
        }
        return HandRank::NONE;
    }
};
