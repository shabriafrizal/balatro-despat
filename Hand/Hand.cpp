#include "Hand.h"
#include <algorithm>

Hand::Hand()
{
}

void Hand::addCard(const Card &card)
{
    cards.push_back(card);
}

void Hand::removeCard(size_t index)
{
    if (index < cards.size())
    {
        cards.erase(cards.begin() + index);
    }
}

const std::vector<Card> &Hand::getCards() const
{
    return cards;
}

size_t Hand::getCardCount() const
{
    return cards.size();
}

void Hand::clear()
{
    cards.clear();
}

void Hand::sortByRank()
{
    std::sort(cards.begin(), cards.end(),
              [](const Card &a, const Card &b)
              {
                  // Sort descending by rank (Ace=14 highest, Two=2 lowest)
                  return static_cast<int>(a.rank) > static_cast<int>(b.rank);
              });
}
