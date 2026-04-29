#pragma once
#include "Hand.h"
#include "HandRank.h"

class PokerHandChecker
{
public:
    virtual ~PokerHandChecker() = default;

    virtual HandRank check(const Hand &hand) = 0;
    void setNext(PokerHandChecker *next);
    HandRank checkChain(const Hand &hand);

protected:
    PokerHandChecker *nextChecker = nullptr;
};
