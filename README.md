# BattleBlaster

A top-down tank shooter built in **Unreal Engine 5** using **C++**, developed as a learning project to practice gameplay programming, AI systems, and game architecture.

---

## Gameplay

The player controls a tank from a top-down perspective and must destroy all enemy towers before being destroyed. Each level starts with a countdown before both the player and towers are activated.

---

## Features

### Player Tank
- Top-down movement with forward/backward drive and rotation
- Mouse-aimed turret with smooth yaw interpolation
- **Dash** — directional dash based on current WASD input, with a yaw spin animation, cooldown, and camera lock during the dash
- **Sprint** — hold Shift to move at increased speed
- Projectile firing toward the cursor

### Tower AI
- Fire range detection using distance checks
- Turret rotation toward the player with yaw alignment threshold before firing
- Dynamic fire rate — rapid re-targeting, slower firing when aligned
- Towers only activate after the round countdown ends

### Projectile System
- Collision-based hit detection
- Applies damage via Unreal's damage pipeline
- Hit particles (Niagara), hit sound, and camera shake on impact
- Launch sound on fire

### Health & Damage
- `UHealthComponent` attached to both tanks and towers
- Uses `OnTakeAnyDamage` delegate
- Death triggers game mode events

### Game Mode
- Tracks tower count and player state
- Handles win (all towers destroyed) and loss (player destroyed) conditions
- Countdown system gates player input and tower AI until round start
- Transitions to next level on victory or restarts on defeat via `UGameInstance`

### UI
- Screen message widget for countdown (Get Ready / 3 / 2 / 1 / Go!)
- Game over message (Victory! / Defeat!)

---

## Architecture

```
ABasePawn
├── ATank        — player-controlled pawn
└── ATower       — AI-controlled enemy
```

- Shared turret rotation, fire logic, and death handling in `ABasePawn`
- `UHealthComponent` is a reusable actor component
- `ABattleBlasterGameMode` coordinates all actors and game state
- `UBattleBlasterGameInstance` persists across levels for level management
- `TWeakObjectPtr` used for cross-actor references to safely handle actor lifetime

---

## Technical Highlights

- Inheritance-based pawn architecture with shared base logic
- `TWeakObjectPtr<ATank>` in towers to avoid dangling pointer crashes
- Timer management with proper `ClearTimer` before actor destruction
- Enhanced Input System for all player controls
- Directional dash calculated from live WASD input vectors at the moment of press
- Dash spin speed tuned so total yaw rotation is a multiple of 360°, preserving facing direction

---

## Built With

- Unreal Engine 5
- C++
- Enhanced Input System
- Niagara Particle System

---

## What I Learned

- Designing a clean inheritance hierarchy for gameplay pawns
- Safe actor reference handling with `TWeakObjectPtr` and `IsValid()`
- Timer lifecycle management and avoiding callbacks on destroyed actors
- Separating concerns across components, pawns, and the game mode
- Unreal's damage pipeline (`ApplyDamage`, `OnTakeAnyDamage`)
- Building UI with `UUserWidget` and `UTextBlock` in C++

---

## Project Status

Learning project — not a complete game. Systems are functional and serve as a foundation for more complex mechanics.
