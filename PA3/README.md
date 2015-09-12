CS 480 - PA3 - 09/16/2015
===
This assignment achieves 4 primary goals.

1. Implements a smaller 'moon' cube that orbits its parent 'planet' cube.

2. Encapsulation of models and relevant functions to a separate class (handles model translations and rotations).

3. Key-press event callbacks for both standard and special key presses.

##Extra Credit
N/A

##Issues Encountered
- Segfault on exit: Program would segfault on exit from  menu. Currently being assessed.

- Arrow key input: GLUT requires a special handler for certain key presses (callback defined through glutSpecialFunc(); ). This handler requires a different callback from the normal keyboard function; therefore, there are two functions that handle different types of key presses (keyboard and arrowkeys).

##Libraries
- GLM (OpenGL Mathematics)
- GLUT (OpenGL Utility Toolkit)

##Keyboard/mouse controls:
- **1/Up Arrow Key:** Toggle planet cube's spin on/off.

- **Left Arrow Key:** Rotate planet counter-clockwise.

- **Right Arrow Key:** Rotate planet clockwise.

- **Left Click:** Toggle cube's direction of spin.

- **Right Click:** Open context menu.

##Instructions for compilation.
>cd build/

>make

##How to run your program.
>cd bin/

>./Matrix.bin

##Team Members
N/A

##References Encountered
N/A

