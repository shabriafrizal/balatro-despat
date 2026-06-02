#pragma once

#include <cstddef>
#include "Hand.h"

class HandGenerator
{
public:
    Hand generateHand(size_t cardCount = 5);
};