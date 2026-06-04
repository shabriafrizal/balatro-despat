#pragma once

namespace SkipReward
{

    /**
     * Timing for when a skip reward command should execute.
     */
    enum class CommandTiming
    {
        Immediate, // Execute right away
        NextBlind, // Execute at the start of the next blind
        NextShop,  // Execute when entering the shop
        NextAnte   // Execute when the ante increments
    };

} // namespace SkipReward
