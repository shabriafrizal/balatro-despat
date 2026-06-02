#include "HandScoreTable.h"

HandScoreEntry HandScoreTable::getScore(HandRank handType) const
{
    switch (handType)
    {
    case HandRank::HIGH_CARD:
        return {5, 1};
    case HandRank::PAIR:
        return {10, 2};
    case HandRank::TWO_PAIR:
        return {20, 2};
    case HandRank::THREE_OF_A_KIND:
        return {30, 3};
    case HandRank::STRAIGHT:
        return {30, 4};
    case HandRank::FLUSH:
        return {35, 4};
    case HandRank::FULL_HOUSE:
        return {40, 4};
    case HandRank::FOUR_OF_A_KIND:
        return {60, 7};
    case HandRank::STRAIGHT_FLUSH:
        return {100, 8};
    case HandRank::ROYAL_FLUSH:
        return {100, 8};
    case HandRank::FIVE_OF_A_KIND:
        return {120, 12};
    case HandRank::FLUSH_HOUSE:
        return {140, 14};
    case HandRank::NONE:
    default:
        return {0, 1};
    }
}
