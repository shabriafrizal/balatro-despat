# Skip Reward Command Pattern Implementation - Design Document

## Overview

Part 2 implements the Command Pattern for deferred reward execution when skipping blinds. Commands encapsulate reward logic with configurable timing, enabling flexible reward distribution without if-else conditionals.

## Core Motivation

Skip rewards need the Command Pattern because:
- **Different logic** - Each reward type modifies state differently
- **Different timing** - Rewards activate at different game phases
- **Deferred execution** - Rewards granted now but executed later
- **Independent effects** - Commands don't depend on each other

## Architecture

### Files Created (10 new files)

#### Command Abstraction
- [RewardCommand.h](RewardCommand.h) - Abstract interface for all reward commands

#### Execution Timing
- [CommandTiming.h](CommandTiming.h) - Enum: Immediate, NextBlind, NextShop, NextAnte

#### Command Wrapper
- [PendingCommand.h](PendingCommand.h) - Wraps command with timing and execution tracking

#### Session State
- [RunSessionState.h](RunSessionState.h) - Mutable game state passed to commands

#### Concrete Commands
- [BonusHandCommand.h](BonusHandCommand.h) / [.cpp](BonusHandCommand.cpp) - Grants +1 hand
- [BonusDiscardCommand.h](BonusDiscardCommand.h) / [.cpp](BonusDiscardCommand.cpp) - Grants +1 discard
- [FreeRerollCommand.h](FreeRerollCommand.h) / [.cpp](FreeRerollCommand.cpp) - Grants free reroll
- [BonusMoneyCommand.h](BonusMoneyCommand.h) / [.cpp](BonusMoneyCommand.cpp) - Grants bonus money (configurable)

#### Command Queue
- [RewardCommandQueue.h](RewardCommandQueue.h) / [.cpp](RewardCommandQueue.cpp) - Manages deferred execution

## Command Execution Flow

### 1. Reward Generation
When a blind is skipped, the `IBlindState` creates reward commands:

```cpp
// In IBlindState::transitionToNextState() (pseudocode)
void BossBlindState::transitionToNextState(BlindManager &manager, bool blindWon)
{
    if (blindWon) {
        auto bonusHand = std::make_unique<BonusHandCommand>();
        manager.queueReward(CommandTiming::NextBlind, std::move(bonusHand));
        
        manager.transitionToState(std::make_unique<AnteProgressionState>(ante + 1));
    }
}
```

### 2. Command Storage
Commands are stored in `RewardCommandQueue` with their timing:

```cpp
struct PendingCommand {
    CommandTiming timing;           // When to execute
    bool executed = false;          // Execution status
    std::unique_ptr<RewardCommand> command;  // The actual command
};
```

### 3. Deferred Execution
At appropriate game checkpoints, queued commands execute:

```cpp
// At start of next blind (pseudocode)
void GameManager::runSession()
{
    // ... gameplay ...
    
    if (blindPassed) {
        // Store rewards for later
        commandQueue.executeCommandsWithTiming(CommandTiming::Immediate, state);
    }
    
    // Next blind phase:
    commandQueue.executeCommandsWithTiming(CommandTiming::NextBlind, state);
}
```

### 4. State Modification
Commands apply effects atomically:

```cpp
// BonusHandCommand::execute() (pseudocode)
void BonusHandCommand::execute(RunSessionState &state)
{
    state.remainingPlays += 1;  // Grants extra hand
}
```

## Command Interface

### RewardCommand Abstract Class
```cpp
class RewardCommand {
public:
    virtual const char* getName() const = 0;           // "Bonus Hand"
    virtual const char* getDescription() const = 0;    // "Gain +1 hand"
    virtual void execute(RunSessionState &state) = 0;  // Apply effect
};
```

### Concrete Commands

#### BonusHandCommand
- **Effect**: `state.remainingPlays += 1`
- **Description**: "Gain +1 hand next blind."
- **Typical Timing**: Immediate or NextBlind

#### BonusDiscardCommand
- **Effect**: `state.remainingDiscards += 1`
- **Description**: "Gain +1 discard next blind."
- **Typical Timing**: Immediate or NextBlind

#### FreeRerollCommand
- **Effect**: `state.freeRerolls += 1`
- **Description**: "Gain 1 free reroll."
- **Typical Timing**: Immediate or NextBlind

#### BonusMoneyCommand (Configurable)
- **Effect**: `state.currentMoney += bonusAmount`
- **Description**: Dynamic (e.g., "+25 Money")
- **Constructor**: `BonusMoneyCommand(int amount)`
- **Typical Timing**: Immediate or NextShop

## Deferred Execution System

### CommandTiming Enum
```cpp
enum class CommandTiming {
    Immediate,    // Execute right away
    NextBlind,    // Execute at next blind start
    NextShop,     // Execute at next shop phase
    NextAnte      // Execute at next ante progression
};
```

### RewardCommandQueue
Manages all pending rewards:
- `enqueue(timing, command)` - Add reward
- `executeCommandsWithTiming(timing, state)` - Execute matching timing
- `getPendingCommandCount()` - For UI ("Pending: 3 rewards")
- `getPendingCommands()` - For UI preview
- `clearAll()` - Reset on run end

## Integration Points

### BlindState → RewardCommand Pipeline
**TODO**: Add reward queueing to `IBlindState`:
```cpp
class IBlindState {
    // ... existing methods ...
    virtual void queueSkipRewards(RewardCommandQueue &queue) = 0;
};
```

Each state implements:
```cpp
void BossBlindState::queueSkipRewards(RewardCommandQueue &queue)
{
    // TODO: Decide which rewards Boss grants
    queue.enqueue(CommandTiming::NextBlind, std::make_unique<BonusHandCommand>());
}
```

### GameManager Integration
**TODO**: Add command queue to GameManager:
```cpp
class GameManager {
private:
    RewardCommandQueue commandQueue;
};
```

### HandPlayer Integration
**TODO**: Execute commands at appropriate phases:
```cpp
bool HandPlayer::handlePlay(...) {
    // ... after blind is passed ...
    commandQueue.executeCommandsWithTiming(CommandTiming::Immediate, state);
    return blindWon;
}
```

## Design Decisions

### 1. RunSessionState vs GameManager State
- **RunSessionState**: Lightweight, command-specific state modifications
- **GameManager**: Full run state including deck, hand, etc.
- **Decision**: Keep separate for command isolation; integrate on use

### 2. BonusMoneyCommand Constructor Parameter
- **Why**: Different skip scenarios grant different money amounts
- **Alternative**: Hardcoded per state or factory pattern
- **Chosen**: Constructor flexibility enables reuse

### 3. PendingCommand Keeps Executed Status
- **Why**: Prevents accidental re-execution
- **Alternative**: Delete executed commands from queue
- **Chosen**: Keep for potential debugging and history

### 4. Queue vs Individual Commands
- **Why**: Batch execution at timing checkpoints
- **Alternative**: Execute immediately as created
- **Chosen**: Queue for flexibility (skip rewards not always immediate)

## Command Chaining (Future Extension)

If commands need to execute sequentially with dependencies:

```cpp
// TODO: Future implementation
class CompositeCommand : public RewardCommand {
    std::vector<std::unique_ptr<RewardCommand>> commands;
    void execute(RunSessionState &state) override {
        for (auto &cmd : commands) {
            cmd->execute(state);
        }
    }
};
```

## Extensibility

### Adding New Reward Types

1. **Create command class**:
   ```cpp
   class BonusJokerCommand : public RewardCommand { /* ... */ };
   ```

2. **Implement interface**:
   - `getName()` - "Bonus Joker Slot"
   - `getDescription()` - "+1 joker slot"
   - `execute()` - `state.jokerSlots += 1`

3. **Queue from states**:
   ```cpp
   queue.enqueue(CommandTiming::NextShop, std::make_unique<BonusJokerCommand>());
   ```

**No modifications needed** to CommandQueue or execution logic.

## Assumptions

1. **RunSessionState is sufficient** - Contains all fields that commands modify
   - TODO: Validate against actual skip reward types

2. **Commands are synchronous** - No async execution needed
   - TODO: Reconsider if animation/delay is required

3. **Commands are deterministic** - Same command always produces same effect
   - Enables potential serialization/replay

4. **No circular command dependencies** - Commands don't queue new commands
   - TODO: If needed, implement command-to-command chaining

5. **Timing checkpoint frequency** - Game calls executeCommandsWithTiming at every phase
   - TODO: Ensure all timing points are covered in GameManager

## Testing Strategy (Not Implemented)

1. **Unit Tests**:
   - Verify each command modifies correct state field
   - Verify execution state tracking (executed flag)
   - Test queue ordering

2. **Integration Tests**:
   - Commands execute at correct timing
   - Multiple commands execute in sequence
   - Commands don't interfere with each other

3. **Regression Tests**:
   - Skip rewards produce same state changes as original logic

## Future Considerations

- **Conditional commands**: Execute only if precondition met
- **Weighted random rewards**: Randomly select from command pool
- **Command serialization**: Save/restore for replays
- **Effect visualization**: UI callbacks during execute()
- **Macro commands**: Bundle multiple commands for UI display
