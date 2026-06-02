#pragma once
#include "../PokerHandChecker.h"

class HighCardChecker : public PokerHandChecker
{
public:
    HandRank check(const Hand &hand) override
    {
        if (hand.getCardCount() >= 5)
        {
            return HandRank::HIGH_CARD;
        }
        return HandRank::NONE;
    }
};
