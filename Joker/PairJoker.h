#pragma once

#include "Joker.h"
#include "../Hand/HandRank.h"

class PairJoker : public Joker
{
public:
    std::string getName() const override;
    std::string getDescription(const ScoreContext &context) const override;
    int getPrice() const override;
    void onScoreCalculated(ScoreContext &context) override;
};
