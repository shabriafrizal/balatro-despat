#include "Hand.h"

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
