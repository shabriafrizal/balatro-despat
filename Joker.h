#pragma once

#include <string>

#include "ScoreContext.h"

class Joker
{
public:
    virtual ~Joker() = default;

    virtual std::string getName() const = 0;
    virtual std::string getDescription(const ScoreContext &context) const = 0;
    virtual void onScoreCalculated(ScoreContext &context) = 0;
};
