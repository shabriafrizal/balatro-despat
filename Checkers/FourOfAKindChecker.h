#pragma once
#include "../PokerHandChecker.h"

class FourOfAKindChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        (void)hand;
        return HandRank::NONE;
    }
};
