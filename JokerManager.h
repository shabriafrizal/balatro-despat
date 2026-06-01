#pragma once

#include <memory>
#include <vector>

#include "Joker.h"

class JokerManager
{
public:
    void addJoker(std::unique_ptr<Joker> joker);
    void clear();
    void applyJokers(ScoreContext &context);
    const std::vector<std::unique_ptr<Joker>> &getJokers() const;

private:
    std::vector<std::unique_ptr<Joker>> jokers;
};
