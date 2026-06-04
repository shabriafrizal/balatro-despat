#pragma once

#include <memory>
#include <vector>

#include "../Joker/Joker.h"
#include "../Joker/JokerManager.h"

/**
 * Shop System: Appears after defeating a blind
 * Offers 3 joker types for purchase
 */
class Shop
{
public:
    Shop();

    /**
     * Display the shop and handle purchasing
     * @param jokerManager Manager to add purchased joker to
     * @param money Player's current money (will be deducted on purchase)
     * @return true if a joker was purchased, false if skipped
     */
    bool displayAndHandle(JokerManager &jokerManager, int &money);

private:
    std::vector<std::unique_ptr<Joker>> shopJokers;

    /**
     * Initialize the 3 shop jokers
     */
    void initializeShopJokers();
};
