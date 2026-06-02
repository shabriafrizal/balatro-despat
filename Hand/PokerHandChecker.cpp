#include "PokerHandChecker.h"

void PokerHandChecker::setNext(PokerHandChecker *next)
{
    nextChecker = next;
}

HandRank PokerHandChecker::checkChain(const Hand &hand)
{
    HandRank result = check(hand);
    if (result == HandRank::NONE && nextChecker != nullptr)
    {
        return nextChecker->checkChain(hand);
    }

    return result;
}
