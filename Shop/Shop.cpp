#include <iostream>
#include <memory>

#include "Shop.h"
#include "../Joker/MultiplierJoker.h"
#include "../Joker/FlatChipJoker.h"
#include "../Joker/PairJoker.h"

Shop::Shop()
{
    initializeShopJokers();
}

void Shop::initializeShopJokers()
{
    shopJokers.clear();
    shopJokers.push_back(std::make_unique<MultiplierJoker>());
    shopJokers.push_back(std::make_unique<FlatChipJoker>());
    shopJokers.push_back(std::make_unique<PairJoker>());
}

bool Shop::displayAndHandle(JokerManager &jokerManager)
{
    // Reinitialize shop jokers for this blind
    initializeShopJokers();

    std::cout << "\n========== SHOP ==========\n";
    std::cout << "Choose a joker to purchase or skip:\n\n";

    // Display shop items
    for (size_t i = 0; i < shopJokers.size(); ++i)
    {
        std::cout << "[" << i << "] " << shopJokers[i]->getName()
                  << " - " << shopJokers[i]->getDescription(ScoreContext{}) << "\n";
    }

    std::cout << "[S]kip shop\n";
    std::cout << "> ";

    std::string choice;
    std::getline(std::cin, choice);

    if (choice == "S" || choice == "s")
    {
        std::cout << "Skipping shop.\n";
        return false;
    }

    // Try to parse choice as index
    try
    {
        int index = std::stoi(choice);
        if (index >= 0 && index < static_cast<int>(shopJokers.size()))
        {
            std::cout << "Purchased: " << shopJokers[index]->getName() << "\n";
            jokerManager.addJoker(std::move(shopJokers[index]));
            return true;
        }
    }
    catch (...)
    {
        // Invalid input
    }

    std::cout << "Invalid choice.\n";
    return false;
}
