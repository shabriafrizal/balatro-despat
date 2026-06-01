#include "HandScoreTable.h"

HandScoreEntry HandScoreTable::getScore(HandRank handType) const
{
    switch (handType)
    {
    default:
        return {0, 1};
    }
}
