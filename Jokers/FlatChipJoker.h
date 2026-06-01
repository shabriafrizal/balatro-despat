#pragma once

#include "../Joker.h"

class FlatChipJoker : public Joker
{
public:
    std::string getName() const override;
    std::string getDescription(const ScoreContext &context) const override;
    void onScoreCalculated(ScoreContext &context) override;
};
