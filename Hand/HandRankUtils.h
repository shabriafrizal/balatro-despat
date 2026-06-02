#pragma once

#include "HandRank.h"

inline const char *handRankToString(HandRank rank)
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
