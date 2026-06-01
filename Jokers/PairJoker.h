#pragma once

#include "../Joker.h"
#include "../HandRank.h"

class PairJoker : public Joker
{
public:
    std::string getName() const override;
    std::string getDescription(const ScoreContext &context) const override;
    void onScoreCalculated(ScoreContext &context) override;
};
