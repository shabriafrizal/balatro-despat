#include "SkipRewardQueue.h"

#include <algorithm>
#include <iostream>

void SkipRewardQueue::enqueue(std::unique_ptr<ISkipRewardCommand> command)
{
    commands.push_back(std::move(command));
}

int SkipRewardQueue::executeAfterNextBlindCommands(int &money, int &chips)
{
    int executed = 0;

    // Collect indices of commands to execute
    std::vector<size_t> toRemove;

    for (size_t i = 0; i < commands.size(); ++i)
    {
        if (commands[i]->executeAfterNextBlind())
        {
            std::cout << "[SkipReward] Executing: "
                      << commands[i]->getDescription()
                      << " (skipped " << commands[i]->getBlindSource() << ")\n";

            int beforeMoney = money;
            int beforeChips = chips;
            commands[i]->execute(money, chips);

            if (money != beforeMoney)
            {
                std::cout << "  +$" << (money - beforeMoney) << " (total: $" << money << ")\n";
            }
            if (chips != beforeChips)
            {
                std::cout << "  +" << (chips - beforeChips) << " bonus chips\n";
            }

            toRemove.push_back(i);
            ++executed;
        }
    }

    // Remove executed commands (reverse order to preserve indices)
    for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it)
    {
        commands.erase(commands.begin() + static_cast<long>(*it));
    }

    return executed;
}

int SkipRewardQueue::executeAfterBossCommands(int &money, int &chips)
{
    int executed = 0;

    std::vector<size_t> toRemove;

    for (size_t i = 0; i < commands.size(); ++i)
    {
        if (!commands[i]->executeAfterNextBlind())
        {
            std::cout << "[SkipReward] Executing (post-Boss): "
                      << commands[i]->getDescription()
                      << " (skipped " << commands[i]->getBlindSource() << ")\n";

            int beforeMoney = money;
            commands[i]->execute(money, chips);

            if (money != beforeMoney)
            {
                std::cout << "  +$" << (money - beforeMoney) << " (total: $" << money << ")\n";
            }

            toRemove.push_back(i);
            ++executed;
        }
    }

    for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it)
    {
        commands.erase(commands.begin() + static_cast<long>(*it));
    }

    return executed;
}

int SkipRewardQueue::executeAll(int &money, int &chips)
{
    int executed = 0;

    for (auto &cmd : commands)
    {
        std::cout << "[SkipReward] Executing: "
                  << cmd->getDescription()
                  << " (skipped " << cmd->getBlindSource() << ")\n";
        cmd->execute(money, chips);
        ++executed;
    }

    commands.clear();
    return executed;
}

bool SkipRewardQueue::isEmpty() const
{
    return commands.empty();
}

size_t SkipRewardQueue::size() const
{
    return commands.size();
}

void SkipRewardQueue::displayPending() const
{
    if (commands.empty())
    {
        std::cout << "[SkipReward] No pending skip rewards.\n";
        return;
    }

    std::cout << "[SkipReward] Pending rewards (" << commands.size() << "):\n";
    for (size_t i = 0; i < commands.size(); ++i)
    {
        std::cout << "  " << (i + 1) << ". "
                  << commands[i]->getDescription()
                  << " (from " << commands[i]->getBlindSource() << ")"
                  << (commands[i]->executeAfterNextBlind()
                          ? " [next blind]"
                          : " [after Boss]")
                  << "\n";
    }
}

void SkipRewardQueue::clear()
{
    commands.clear();
}