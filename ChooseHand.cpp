#include "ChooseHand.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

Hand ChooseHand::chooseFromHand(const Hand &generatedHand, const std::vector<size_t> &indices)
{
    Hand selectedHand;
    const auto &cards = generatedHand.getCards();

    // Validate indices and add selected cards
    for (size_t index : indices)
    {
        if (index >= cards.size())
        {
            throw std::out_of_range("Card index out of range");
        }
        selectedHand.addCard(cards[index]);
    }

    return selectedHand;
}

Hand ChooseHand::discardFromHand(const Hand &generatedHand, const std::vector<size_t> &indices)
{
    Hand remainingHand;
    const auto &cards = generatedHand.getCards();

    // Create a set of indices to discard for O(1) lookup
    std::vector<size_t> sortedIndices = indices;
    std::sort(sortedIndices.begin(), sortedIndices.end());

    // Validate all indices
    for (size_t index : sortedIndices)
    {
        if (index >= cards.size())
        {
            throw std::out_of_range("Card index out of range");
        }
    }

    // Add cards that are not in the discard list
    for (size_t i = 0; i < cards.size(); ++i)
    {
        if (!std::binary_search(sortedIndices.begin(), sortedIndices.end(), i))
        {
            remainingHand.addCard(cards[i]);
        }
    }

    return remainingHand;
}

Hand ChooseHand::chooseFromHandWithUserInput(const Hand &generatedHand)
{
    const auto &cards = generatedHand.getCards();
    std::vector<size_t> chosenIndices;

    std::cout << "\nEnter card indices to choose (space-separated), then press Enter:\n";
    std::cout << "Example: 0 2 4\n";
    std::cout << "> ";

    std::string input;
    std::getline(std::cin, input);

    // Parse input
    std::istringstream iss(input);
    size_t index;

    while (iss >> index)
    {
        if (index >= cards.size())
        {
            std::cerr << "Warning: Index " << index << " is out of range, skipping...\n";
            continue;
        }
        chosenIndices.push_back(index);
    }

    if (chosenIndices.empty())
    {
        std::cerr << "No valid cards selected!\n";
        throw std::invalid_argument("No cards were chosen");
    }

    return chooseFromHand(generatedHand, chosenIndices);
}
