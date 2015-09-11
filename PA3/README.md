CS 480 - PA3 - 09/16/2015
===
This assignment achieves 4 primary goals.

1. Implements a smaller 'moon' cube that orbits its parent 'planet' cube.

2. Encapsulation of models and relevant functions to a separate class (handles model translations and rotations).

3. Keybindings for managing planet cube spin/orbit.

4. Eliminated segfault on exit from menu bug.

##Extra Credit
N/A

##Issues Encountered
- Segfault on exit: Program would segfault on exit from  menu. This was due to GLUT redefining the exit(0) call. Including STDLIB.h before the GLUT libraries fixed the definition of exit(0).

##Libraries
- GLM (OpenGL Mathematics)
- GLUT (OpenGL Utility Toolkit)

##Keyboard/mouse controls:
- *1:* Toggle planet cube's spin on/off.

- *Left Click/Left & Right Arrow Keys:* Toggle cube's direction of spin.

- *Right Click:* Open context menu.

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

