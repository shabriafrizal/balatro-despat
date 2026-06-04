#pragma once

namespace SkipReward
{

    /**
     * Mutable game state that skip reward commands can modify.
     * Lightweight snapshot passed to commands at execution time.
     */
    struct RunSessionState
    {
        int &remainingPlays;
        int &remainingDiscards;
        int &currentMoney;
        int &freeRerolls;
    };

} // namespace SkipReward
