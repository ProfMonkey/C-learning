<div align="center">

# 🐍 C Learning Journey

**Learning C by building real projects — from basic console programs to game AI.**

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![Status](https://img.shields.io/badge/Status-Active%20Learning-brightgreen)

</div>

---

## 🚀 About This Repository

This repository records my C programming learning journey through progressively larger projects.

The main project is a **Snake AI series**, evolving from manual control to rule-based decision making and then reinforcement learning.

---

## 🐍 Snake AI Evolution

| Version | Stage | Main Idea | Status |
|---|---|---|---|
| **V1** | Manual Snake | Player control, food, growth, collision and scoring | ✅ Complete |
| **V2** | Rule-Based Bot | Safety checks, food distance and visit penalties | ✅ Complete |
| **V3** | Q-Learning Snake | Turn the game into a trainable environment | 🚧 In Progress |
| **V4** | Neural Network | Learn actions with a small neural network | 🧭 Planned |

### V1 — Manual Snake

The first complete playable version, using a circular-array design for the snake body.

📁 [`v1/`](./v1)

### V2 — Rule-Based Bot

The bot evaluates forward / left / right moves using safety, food distance and visit history.

📁 [`v2/`](./v2)

### V3 — Q-Learning

V3 starts from the stable V2 game and gradually turns it into a reinforcement-learning environment.

```text
State → Choose Action → Game Step → Reward → Update Q Table → Next State
```

Planned first state representation:

- danger ahead / left / right
- food ahead / behind / left / right
- 128 states
- 3 actions: STRAIGHT / LEFT / RIGHT

📁 [`v3/`](./v3)

---

## 🗂 Repository Structure

```text
C-learning/
├─ basics/                    # Early C exercises
│  ├─ hello.c
│  ├─ student_report.c
│  └─ students.txt
│
├─ v1/                        # Manual Snake
│  └─ snake_v1.c
│
├─ v2/                        # Rule-based Snake bot
│  ├─ snake_v2.c
│  ├─ snake_v2_game.c
│  └─ snake_v2_game.h
│
├─ v3/                        # Q-learning version in progress
│  ├─ snake_v3.c
│  ├─ snake_v3_game.c
│  └─ snake_v3_game.h
│
├─ archive/
│  └─ v2_early/               # Preserved earlier V2 snapshot
│
├─ .vscode/
├─ .gitignore
└─ README.md
```

The `archive/` folder keeps older code snapshots that are still useful for comparing how the project evolved.

---

## 🛠 Development Environment

The current Snake versions are developed and tested primarily on **Windows**.

They currently use Windows-specific APIs such as:

- `windows.h`
- `conio.h`
- `Sleep()`

So the current source code is **not intended to compile unchanged on Linux**.

The focus right now is learning C, program structure and game AI. Cross-platform support can be added later when the project reaches a more mature stage.

### Current toolchain

```text
OS: Windows
Editor: VS Code
Language: C
Compiler: GCC
Terminal: PowerShell
```

---

## ▶️ Build & Run

### V1

```powershell
cd v1
gcc snake_v1.c -o snake_v1.exe
.\snake_v1.exe
```

### V2

```powershell
cd v2
gcc snake_v2.c snake_v2_game.c -o snake_v2.exe
.\snake_v2.exe
```

### V3

```powershell
cd v3
gcc snake_v3.c snake_v3_game.c -o snake_v3.exe
.\snake_v3.exe
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
- [ ] Add cross-platform support later

---

<div align="center">

**Built one step at a time.**

</div>