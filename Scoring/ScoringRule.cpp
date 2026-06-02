#include <iostream>

#include "../Hand/HandRankUtils.h"
#include "../Hand/HandScoreTable.h"
#include "ScoringRule.h"
#include "../Hand/Checkers/FlushHouseChecker.h"
#include "../Hand/Checkers/FiveOfAKindChecker.h"
#include "../Hand/Checkers/RoyalFlushChecker.h"
#include "../Hand/Checkers/StraightFlushChecker.h"
#include "../Hand/Checkers/FourOfAKindChecker.h"
#include "../Hand/Checkers/FullHouseChecker.h"
#include "../Hand/Checkers/FlushChecker.h"
#include "../Hand/Checkers/StraightChecker.h"
#include "../Hand/Checkers/ThreeOfAKindChecker.h"
#include "../Hand/Checkers/TwoPairChecker.h"
#include "../Hand/Checkers/PairChecker.h"
#include "../Hand/Checkers/HighCardChecker.h"

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