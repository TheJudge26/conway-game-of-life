# Conway's Game of Life (C & SDL2)

![alt text](demo-1.gif)

## Interactive Controls & Mechanics

The engine utilizes an event driven loop (via `SDL_PollEvent`) that allows you to manipulate the memory matrix and simulation state in real-time. 

* **`Spacebar` (Pause / Play ):** Toggles the simulation's update loop. Freezing time puts the engine into a sandbox mode, allowing you to manually click and draw complex cellular structures (like Gliders or blinkers) without them dying of underpopulation before you finish drawing.
* **`Enter` (Randomize Matrix):** Instantly triggers the `rand_game_matrix` function. This iterates through the entire 1D array and randomizes the memory addresses, overwriting the canvas with a brand-new, chaotic pattern of static.
* **`Backspace` (Clear Canvas):** Triggers the `blank_game_matrix` function. This acts as a master eraser, looping through the matrix and setting every single cell's state to `0`. It instantly wipes the board to black, providing a blank slate for custom drawing.
* **`Left Mouse Click` (Toggle Cell):** Calculates the exact 1D matrix index based on your 2D screen cursor coordinates and flips the living state of that specific cell.