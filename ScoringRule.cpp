#include <iostream>

#include "HandRankUtils.h"
#include "HandScoreTable.h"
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
    int cardRankToChips(Card::Rank rank)
    {
        int rawRank = static_cast<int>(rank);
        if (rawRank >= static_cast<int>(Card::Rank::TWO) && rawRank <= static_cast<int>(Card::Rank::TEN))
        {
            return rawRank;
        }

        switch (rank)
        {
        case Card::Rank::JACK:
        case Card::Rank::QUEEN:
        case Card::Rank::KING:
            return 10;
        case Card::Rank::ACE:
            return 11;
        default:
            return 0;
        }
    }
}

BaseScore ScoringRule::calculateBaseScore(const Hand &hand) const
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

    HandScoreTable scoreTable;
    HandScoreEntry entry = scoreTable.getScore(rank);

    int cardChips = 0;
    for (const Card &card : hand.getCards())
    {
        cardChips += cardRankToChips(card.rank);
    }

    BaseScore result;
    result.handType = rank;
    result.chips = entry.chips + cardChips;
    result.multiplier = entry.multiplier;
    return result;
}

int ScoringRule::scoreHand(const Hand &hand) const
{
    BaseScore baseScore = calculateBaseScore(hand);
    return baseScore.chips * baseScore.multiplier;
}