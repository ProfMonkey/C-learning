<div align="center">

# 🐍 C Learning Journey

**Learning C by building real projects — from basic console programs to game AI.**

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Status](https://img.shields.io/badge/Status-Active%20Learning-brightgreen)

</div>

---

## 🚀 About This Repository

This repository records my C programming learning journey.

Instead of only doing isolated exercises, I am building projects step by step and continuously upgrading them.
The current main project is a **Snake game series**, evolving from manual control to rule-based AI and then toward reinforcement learning.

---

## 🐍 Snake AI Evolution

| Version | Stage | Main Idea | Status |
|---|---|---|---|
| **V1** | Manual Snake | Player control, movement, food, growth, collision and score | ✅ Complete |
| **V2** | Rule-Based Bot | Safety checks, food distance and visit penalties | ✅ Complete |
| **V3** | Q-Learning Snake | Convert the game into a trainable environment and learn actions | 🚧 In Progress |
| **V4** | Neural Network | Use a small neural network to choose actions | 🧭 Planned |

### V1 — Manual Snake

The first complete playable version.

Main concepts practiced:

- Arrays
- Functions
- Keyboard input
- Collision detection
- Game loop
- Circular-array snake body management

📁 [`snake/`](./snake)

### V2 — Rule-Based Bot

The snake can play automatically using hand-written rules.

The bot evaluates:

- whether moving forward / left / right is safe
- Manhattan distance to food
- how often a position has been visited

📁 [`v2/`](./v2)

### V3 — Q-Learning

V3 starts from the stable V2 game and gradually turns it into a reinforcement-learning environment.

Planned pipeline:

```text
State
  ↓
Choose Action
  ↓
Game Step
  ↓
Reward
  ↓
Update Q Table
  ↓
Next State
```

The first state representation will use:

- danger ahead
- danger left
- danger right
- food ahead
- food behind
- food left
- food right

That gives **2^7 = 128 states** and **3 actions**:

```text
STRAIGHT
LEFT
RIGHT
```

📁 [`v3/`](./v3)

---

## 🗂 Repository Structure

```text
C-learning/
├─ hello.c
├─ 2p.c
├─ students.txt
├─ snake/              # V1 manual Snake
├─ v2/                 # Rule-based Snake bot
├─ v3/                 # Q-learning version in progress
└─ README.md
```

---

## 🛠 Build

The Snake project is currently developed on Windows with GCC.

For V3:

```powershell
cd v3
gcc snake_v3.c snake_v3_game.c -o snake_v3.exe
.\\snake_v3.exe
```

---

## 📚 What I Am Practicing

```text
C basics
   ↓
Pointers / arrays / structs
   ↓
File I/O and modular programs
   ↓
Data structures and algorithms
   ↓
Game AI
   ↓
Reinforcement learning
```

The goal is not just to make programs work, but to gradually improve **code structure, debugging ability, algorithmic thinking, and engineering habits**.

---

## 🧭 Roadmap

- [x] Build a playable Snake game
- [x] Implement circular-array snake movement
- [x] Add a rule-based bot
- [x] Add safety checking and simple path preference
- [ ] Refactor V3 into a trainable game environment
- [ ] Add state encoding
- [ ] Add Q-table and ε-greedy exploration
- [ ] Train for thousands of episodes
- [ ] Save / load the trained Q-table
- [ ] Compare V2 and V3 performance
- [ ] Experiment with a small neural-network version

---

<div align="center">

**Built one step at a time.**

</div>