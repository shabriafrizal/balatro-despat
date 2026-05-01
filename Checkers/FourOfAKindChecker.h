#pragma once
#include "../PokerHandChecker.h"

class FourOfAKindChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        const PokerHandUtils::HandAnalysis analysis = PokerHandUtils::analyzeHand(hand);
        if (PokerHandUtils::hasNOfKind(analysis, 4))
        {
            return HandRank::FOUR_OF_A_KIND;
        }
        return HandRank::NONE;
    }
};
