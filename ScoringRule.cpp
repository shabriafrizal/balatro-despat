#include <iostream>

#include "ScoringRule.h"
#include "Checkers/FlushHouseChecker.h"
#include "Checkers/FiveOfAKindChecker.h"
#include "Checkers/RoyalFlushChecker.h"
#include "Checkers/StraightFlushChecker.h"
#include "Checkers/FourOfAKindChecker.h"
#include "Checkers/FullHouseChecker.h"
#include "Checkers/FlushChecker.h"
#include "Checkers/StraightChecker.h"
#include "Checkers/ThreeOfAKindChecker.h"
#include "Checkers/TwoPairChecker.h"
#include "Checkers/PairChecker.h"
#include "Checkers/HighCardChecker.h"

namespace
{
    const char *handRankToString(HandRank rank)
    {
        switch (rank)
        {
        case HandRank::HIGH_CARD:
            return "High Card";
        case HandRank::PAIR:
            return "Pair";
        case HandRank::TWO_PAIR:
            return "Two Pair";
        case HandRank::THREE_OF_A_KIND:
            return "Three of a Kind";
        case HandRank::STRAIGHT:
            return "Straight";
        case HandRank::FLUSH:
            return "Flush";
        case HandRank::FULL_HOUSE:
            return "Full House";
        case HandRank::FOUR_OF_A_KIND:
            return "Four of a Kind";
        case HandRank::STRAIGHT_FLUSH:
            return "Straight Flush";
        case HandRank::ROYAL_FLUSH:
            return "Royal Flush";
        case HandRank::FIVE_OF_A_KIND:
            return "Five of a Kind";
        case HandRank::FLUSH_HOUSE:
            return "Flush House";
        default:
            return "None";
        }
    }
}

int ScoringRule::scoreHand(const Hand &hand)
{
    std::cout << "Calculating hand score...\n";

    FlushHouseChecker flushHouseChecker;
    FiveOfAKindChecker fiveOfAKindChecker;
    RoyalFlushChecker royalFlushChecker;
    StraightFlushChecker straightFlushChecker;
    FourOfAKindChecker fourOfAKindChecker;
    FullHouseChecker fullHouseChecker;
    FlushChecker flushChecker;
    StraightChecker straightChecker;
    ThreeOfAKindChecker threeOfAKindChecker;
    TwoPairChecker twoPairChecker;
    PairChecker pairChecker;
    HighCardChecker highCardChecker;

    flushHouseChecker.setNext(&fiveOfAKindChecker);
    fiveOfAKindChecker.setNext(&royalFlushChecker);
    royalFlushChecker.setNext(&straightFlushChecker);
    straightFlushChecker.setNext(&fourOfAKindChecker);
    fourOfAKindChecker.setNext(&fullHouseChecker);
    fullHouseChecker.setNext(&flushChecker);
    flushChecker.setNext(&straightChecker);
    straightChecker.setNext(&threeOfAKindChecker);
    threeOfAKindChecker.setNext(&twoPairChecker);
    twoPairChecker.setNext(&pairChecker);
    pairChecker.setNext(&highCardChecker);

    HandRank rank = flushHouseChecker.checkChain(hand);
    std::cout << "Hand rank: " << handRankToString(rank) << "\n";

    return static_cast<int>(rank);
}