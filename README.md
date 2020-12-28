# Minesweeper
## *Documentation*
Documentation can be found here [Doxygen](doxygen/)
## *Compilation*
Compile using the command line: `gcc -Wall -Wextra -pedantic -Wno-unused-parameter -o minesweeper minesweeper.c checkingFunctions.c prints.c generatePlayfield.c revealFields.c playerInfo.c`  
## *Execution*
### *Calling*
Run the program by calling `./minesweeper 10x10 20`  
The first argument must be a 3 or 5 character matrix, e.g. `5x5` or `15x15`.  
The second argument must be a one or two digit number of mines for the game, e.g. `5` or `15`.  
### *Runtime*
First, the user has to enter a name. 
If the player is known, statistics will be loaded.  
Afterwards, the matrix will be generated and the user can start to play.  
The user can choose fields in the matrix by writing the column name and the row number. He can also add a question mark in front of it, to mark that field as a mine.  
Examples: `A2, D10, ?B4, ?C15`  
### *How to win*
You can win by either opening all correct fields or by marking all mines correctly.  
## *Completed Tasks*
Task description can be found here [Tasks](TASK.adoc)
### *Project Tasks*
:white_check_mark: **Main Task (30 points)**  
:white_check_mark: **Reveal neighbor zeroes Task (15 points)**  
:white_check_mark: **Read Matrix and Mines from argv Task (15 points)**  
:white_check_mark: **Mark a mine [?] Task (15 points)**  
:white_check_mark: **Save/Load Player Statistics Task (15 points)**  
:wavy_dash: **Abort/Load the game Task (15 points)**  
:x: **Use ncurses Task (25 points)**
### *Additional features*
* HELP, write `help` or `h` into the cmd to get a tip  
* EXIT, write `exit` or `e` into the cmd to exit the game without saving statistics & game  
