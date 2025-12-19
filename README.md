
# Console_Snake_Game 🐍

A fully playable, console-based Snake game written in **C**.
This project focuses on core programming fundamentals: data structures, file handling, game loops, and low-level console control.

Everything happens in the terminal. No graphics libraries. No shortcuts. Just logic, timing, and careful control of characters on the screen.

## Screenshots

## Welcome Screen
<img width="719" height="729" alt="image" src="https://github.com/user-attachments/assets/f2898175-da59-4fe5-8f64-744ca2d6eed8" />

## Display High Score
<img width="718" height="724" alt="image" src="https://github.com/user-attachments/assets/f175e345-2bf3-4346-9b85-427e9ae1dd4d" />

## Level Choose Screen
<img width="716" height="726" alt="image" src="https://github.com/user-attachments/assets/cccf3efe-0def-469d-8ebc-64bcdeef59fe" />

## In-Game Screen
<img width="717" height="832" alt="image" src="https://github.com/user-attachments/assets/a4e2e295-9070-4ef5-83ec-21ceb2c52b1a" />

## Pause Screen
<img width="675" height="757" alt="image" src="https://github.com/user-attachments/assets/d2671a9f-c4c8-4518-bdd7-a5f4d1f9032e" />

## Game Over Screen
<img width="715" height="725" alt="image" src="https://github.com/user-attachments/assets/3ba87477-ba44-4ad7-9efe-7391e98395e9" />


---

## 🎮 Features

• **Five difficulty levels** i.e. Easy, Medium, Hard, Extreme, Legendary

• **Persistent high scores** stored using file handling

• **Real-time input** without pressing Enter

• **Smooth rendering** using cursor repositioning instead of clearing the screen

• **Colorful console UI** using ANSI escape codes and Windows API

• **Pause, restart, and menu navigation**

• **Sound feedback** when food is eaten

---

## 🛠 Technical Implementation & Concepts

This project is intentionally low-level. Every system is built from scratch using standard C and Windows-specific libraries.

### 1. Data Structures (`struct`)

Game entities are modeled using structures to keep logic organized and readable.

• `SnakeHead` stores the current head coordinates

• `SnakeTail` is an array storing all body segment positions

• `Food` stores the current food location

This separation makes movement, collision detection, and rendering predictable and easy to reason about.

---

### 2. Game Loop Design

The core loop lives inside `gameEngine()` and follows a classic structure:

1. Read keyboard input (non-blocking)
   
2. Update snake direction
   
3. Move snake body and head
   
4. Check for collisions
   
5. Handle food consumption
    
6. Render the entire frame
    
7. Delay execution based on difficulty

The delay is controlled by `Sleep(refreshRate)`, making speed scale naturally with difficulty.

---

### 3. Snake Movement Logic

The snake moves using a simple but effective algorithm:

• Each tail segment copies the position of the segment in front of it

• The first tail segment follows the head

• The head moves one step based on the last valid direction

Reverse direction inputs are blocked to prevent instant self-collision.

---

### 4. Collision Detection

Game-over conditions are checked every frame:

• **Wall collision** —> head touches the boundary

• **Self collision** —> head overlaps any tail segment

This is handled by iterating through the tail array and comparing coordinates.

---

### 5. Food Generation Algorithm

Food is generated randomly inside the play area using `rand()` and `time()`.

The program ensures that food never spawns:

• on the snake’s head

• on any part of the snake’s body

A helper function (`overlapWithBody`) verifies safe placement before confirming food coordinates.

---

### 6. File Handling (High Score Persistence)

High scores are saved permanently using standard file I/O:

• On startup, the program checks for `do_not_delete.arghya`

• If missing, the file is created and initialized

• Scores are stored separately for each difficulty level

• On Game Over, scores are updated and written back to the file

This demonstrates real-world usage of `fopen`, `fprintf`, `fscanf`, and file validation.

---

### 7. Console Rendering & Windows API

Instead of repeatedly clearing the screen (which causes flicker), the game uses:

• `SetConsoleCursorPosition()` to redraw frames

• `hideCursor()` to remove the blinking cursor

• ANSI escape codes for color output

This results in smooth animation and a stable console UI.

---

### 8. Input Handling

Keyboard input is captured using:

• `_kbhit()` to detect key presses

• `_getch()` to read input instantly

Arrow keys and WASD are both supported. Extended key codes are handled manually for full control.

---

## 🚀 How to Run

### Requirements

• Windows OS

• GCC (MinGW) or any standard C compiler

### Compile

```bash
gcc main.c -o SnakeGame.exe
```

### Run

```bash
SnakeGame.exe
```

---

## 🕹 Controls

| Key   | Action            |
| ----- | ----------------- |
| W / ↑ | Move Up           |
| S / ↓ | Move Down         |
| A / ← | Move Left         |
| D / → | Move Right        |
| P     | Pause / Resume    |
| H     | View High Scores  |
| Enter | Confirm Selection |

---

## 📸 Sample Console View (ASCII Charecter)

## Welcome Screen
```text
# # # # # # # # # # # # # # # # # # # # #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                Welcome                #
#       Console-Based Snake Game        #
#                                       #
#                                       #
#        Press any key to start         #
#                                       #
#      Press 'h' to see high score      #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
# # # # # # # # # # # # # # # # # # # # #
```

## Display High Score
```text
# # # # # # # # # # # # # # # # # # # # #
#                                       #
#                                       #
#                                       #
#                                       #
#             High Scores:              #
#                                       #
#           Easy      :   10            #
#           Medium    :   30            #
#           Hard      :   50            #
#           Extreme   :   40            #
#           Legendary :   40            #
#                                       #
#         Press any key to back         #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
# # # # # # # # # # # # # # # # # # # # #
```

## Level Choose Screen
```text
# # # # # # # # # # # # # # # # # # # # #
#                                       #
#                                       #
#                                       #
#                                       #
#         Please choose a level         #
#            and press enter            #
#                                       #
#                 > Easy                #
#                Medium                 #
#                 Hard                  #
#                Extreme                #
#               Legendary               #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
# # # # # # # # # # # # # # # # # # # # #
```

## In-Game screen
```text
Snake Game                 Dificulty Hard
# # # # # # # # # # # # # # # # # # # # #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                 * * * * * * @     &   #
#                 *                     #
#                 *                     #
#                 *                     #
#                 *                     #
#                 *                     #
#                 *                     #
#                 *                     #
#                 *                     #
#                 * * * * *             #
#                                       #
# # # # # # # # # # # # # # # # # # # # #
Max Score: 160         Current Score: 160
Press 'p' for pause and resume
```

## Pause Screen
```text
Snake Game                 Dificulty Hard
# # # # # # # # # # # # # # # # # # # # #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#              Game Paused              #
#                                       #
#                Resume                 #
#                Restart                #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
# # # # # # # # # # # # # # # # # # # # #
Max Score: 160         Current Score:   0
Press 'p' for pause and resume
```

## Game Over Screen
```text
# # # # # # # # # # # # # # # # # # # # #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#            Congratulation             #
#          New high score:  160         #
#                                       #
#               Game Over               #
#                                       #
#                > Restart              #
#                 Exit                  #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
#                                       #
# # # # # # # # # # # # # # # # # # # # #
```

---

## 📚 Learning Outcomes

This project demonstrates:

• Structured programming in C

• Real-time input handling

• Console graphics without external libraries

• File-based data persistence

• Game loop design and state management

• Problem-solving through logic and constraints
