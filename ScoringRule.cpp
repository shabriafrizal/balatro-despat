#include <iostream>
#include "ScoringRule.h"
#include "Hand.h"
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

int ScoringRule::scoreHand()
{
    std::cout << "Calculating hand score...\n";

    Hand hand;

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
    (void)rank;

    return 5;
}