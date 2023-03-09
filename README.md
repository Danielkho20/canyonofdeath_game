# canyonofdeath_game

The following is a simple implementation of the game Canyon of Death in C with ncurses as the interface for the game. 

The principle of the game is really simple:
A cyclist (represented by a '^' at the bottom of the terminal window) must ride down a canyon without hitting the edges (represented by '*').
Once the game has started, at each clock stroke the character moves down the canyon by one position. This is illustrated by the fact that each line is shifted one 
position downwards (except for the lowest line that has passed the horizon) and that a down (except for the lowest line which, having passed the horizon, is no longer 
displayed) and that a new line is displayed at the highest position. 

The canyon being sinuous, is randomly is randomly shifted by one space to the left or to the right with respect to the the previous highest line with probability 1/3 
in both cases (so it remains unchanged with probability 1/3).

The goal of the game is to get as far down the canyon as possible without crashing. Once the cyclist crashes, that round is finished and the final score will be calculated
and displayed. 
