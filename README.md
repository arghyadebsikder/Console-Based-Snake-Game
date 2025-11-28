# Console-Based Snake Game in C

A small game built for the terminal. Although it's not completed yet. There are some room for improvement. it's Simple on the surface, but underneath it runs a tight little engine of movement, collision, timing and character-based rendering. Everything happens inside the console, like the old days when imagination did most of the graphics work.

This project was created for a C programming lab assignment. The goal was straightforward: bring the classic Snake game to life using pure C and a handful of system calls. The game relies on ASCII characters, non-blocking input, and some Windows-specific functions to keep the screen moving smoothly without flicker.

### What the game offers

You pick a difficulty level, drop into a boxed arena and start guiding the snake around. It moves even when you don’t press anything. Food spawns at random positions, the snake grows, the score climbs, and space gets tighter. Eventually you hit a wall or bite your own tail. The screen freezes for a breath, then you decide whether to restart or call it a day.

The whole thing runs on a continuous loop: input, movement, collision, drawing. No fancy libraries. No graphics engine. Just logic and timing stitched together in C.

### Core features

• Pure console rendering using ASCII characters
• Smooth non-blocking input using `<conio.h>`
• Multiple difficulty levels that adjust game speed
• Clean movement logic, each tail segment follows the path of the one ahead
• Random food placement that avoids the snake’s body
• Game Over menu with restart and exit options
• Pause and resume
• Track current score and max score during the session

### Technical notes

The code stays close to the metal. Cursor movement and screen clearing depend on Windows console APIs. Random generation handles collisions carefully to avoid spawning food inside the snake. Everything is built around a fixed-size grid defined at the top of the file.

The project follows the requirements defined in the attached lab spec, including collision logic, growth rules and clean rendering.

### How to run

Compile with any Windows-friendly C compiler:

```
gcc Console_Based_Snake_Game.c -o snake
```

Then run:

```
./snake
```

The game opens with a welcome screen, then lets you choose difficulty before you enter the arena.
