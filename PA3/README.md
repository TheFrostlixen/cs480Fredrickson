CS 480 - PA3 - 09/16/2015
===
This assignment achieves 4 primary goals.

1. Implements a smaller 'moon' cube that orbits its parent 'planet' cube.

2. Encapsulation of models and relevant functions to a separate class (handles all model calculations).

3. Key-press event callbacks for both standard and special key presses.

##Extra Credit
N/A

##Issues Encountered
- Segfault on exit: Program would segfault on exit from  menu. Currently being assessed.

- Arrow key input: GLUT requires a special handler for certain key presses (callback defined through glutSpecialFunc(); ). This handler requires a different callback from the normal keyboard function; therefore, there are two functions that handle different types of key presses (keyboard and arrowkeys).

- Declaring the translation and rotation angles in their respective functions caused strange spin behaviors. Moved both variables to be members of the Model class.

##Libraries
- GLM (OpenGL Mathematics)
- GLUT (OpenGL Utility Toolkit)

##Keyboard/mouse controls:
- **1/Up Arrow Key:** Toggle planet cube's spin on/off.

- **Left Arrow Key:** Set planet spin counter-clockwise.

- **Right Arrow Key:** Set planet spin clockwise.

- **Left Click/Down Arrow Key:** Toggle cube's direction of spin.

- **Right Click:** Open context menu.

- **Escape:** Exit the game.

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

