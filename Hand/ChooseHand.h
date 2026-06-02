#pragma once

#include <vector>
#include <cstddef>
#include "Hand.h"

class ChooseHand
{
public:
    // Choose cards from a hand based on indices
    // indices: array of card indices to select (0-based)
    // Returns: a new Hand containing only the selected cards
    Hand chooseFromHand(const Hand &generatedHand, const std::vector<size_t> &indices);

    // Discard cards from a hand based on indices
    // indices: array of card indices to remove (0-based)
    // Returns: a new Hand without the discarded cards
    Hand discardFromHand(const Hand &generatedHand, const std::vector<size_t> &indices);

    // Choose cards from a hand with user input
    // Prompts user to enter card indices
    // Returns: a new Hand containing the user-selected cards
    Hand chooseFromHandWithUserInput(const Hand &generatedHand);
};
