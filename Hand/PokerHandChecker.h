#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <initializer_list>
#include <vector>

#include "Hand.h"
#include "HandRank.h"

namespace PokerHandUtils
{
    struct HandAnalysis
    {
        size_t cardCount = 0;
        std::array<int, 15> rankCounts{};
        std::array<int, 4> suitCounts{};
        std::vector<int> uniqueRanks;
        bool isFlush = false;
        bool isStraight = false;
        bool isWheelStraight = false;
    };

    inline HandAnalysis analyzeHand(const Hand &hand)
    {
        HandAnalysis analysis;
        analysis.cardCount = hand.getCardCount();
        analysis.uniqueRanks.reserve(analysis.cardCount);

        const std::vector<Card> &cards = hand.getCards();
        for (const Card &card : cards)
        {
            int rank = static_cast<int>(card.rank);
            int suit = static_cast<int>(card.suit);
            if (rank >= 2 && rank < static_cast<int>(analysis.rankCounts.size()))
            {
                ++analysis.rankCounts[rank];
            }
            if (suit >= 0 && suit < static_cast<int>(analysis.suitCounts.size()))
            {
                ++analysis.suitCounts[suit];
            }
        }

        for (int rank = 2; rank <= 14; ++rank)
        {
            if (analysis.rankCounts[rank] > 0)
            {
                analysis.uniqueRanks.push_back(rank);
            }
        }

        if (analysis.cardCount == 5)
        {
            for (int count : analysis.suitCounts)
            {
                if (count == static_cast<int>(analysis.cardCount))
                {
                    analysis.isFlush = true;
                    break;
                }
            }

            if (analysis.uniqueRanks.size() == analysis.cardCount)
            {
                int minRank = analysis.uniqueRanks.front();
                int maxRank = analysis.uniqueRanks.back();
                if (maxRank - minRank + 1 == static_cast<int>(analysis.cardCount))
                {
                    analysis.isStraight = true;
                }
                else if (analysis.uniqueRanks == std::vector<int>({2, 3, 4, 5, 14}))
                {
                    analysis.isStraight = true;
                    analysis.isWheelStraight = true;
                }
            }
        }

        return analysis;
    }

    inline int countRanksWithCount(const HandAnalysis &analysis, int count)
    {
        int result = 0;
        for (int rank = 2; rank <= 14; ++rank)
        {
            if (analysis.rankCounts[rank] == count)
            {
                ++result;
            }
        }
        return result;
    }

    inline bool hasNOfKind(const HandAnalysis &analysis, int count)
    {
        return countRanksWithCount(analysis, count) > 0;
    }

    inline bool hasRanks(const HandAnalysis &analysis, std::initializer_list<int> ranks)
    {
        for (int rank : ranks)
        {
            if (analysis.rankCounts[rank] == 0)
            {
                return false;
            }
        }
        return true;
    }
}

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
