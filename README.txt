Author: Connor Ballie 101262280, Aaron Payne 101260892
Purpose: To create a program that is a multithreaded simulation of Phasmophobia in the terminal where there is a house of connected rooms along with a wandering ghost and 4 hunters. The goals is for the hunter to navigate around the house to pick up three distinct pieces of evidence to identify the ghost meaning the hunters win. The ghost wins by scaring all of the hunter. The program makes use of different data structures along using dynamic memory and threading to create this simulation. 

List of Source Files:
    - main.c: File that contains the code for the main control flow for this project including creating the threads that needs to be compiled to run
    - rooms.c: File that contains the code for creating and building rooms within a house along with freeing dynamically allocated memory within a room that needs to be compiled to run
    - ghost.c: File that contains the code for the ghost functionally that need to be compiled to run
    - evidence.c: File that contains the code to drop evidence from the ghost into a room and for a hunter to pick up and add evidence to their shared evidence list that need to be compiled to run
    - house.c: File that contains all of the implementation to build a house and free allocated memory within the house that need to be compiled to run
    - hunters.c: File that contains all of the hunter functionality that need to be compiled to run
    - logger.c: File that contains predetermined functions to print actions within the game that need to be compiled to run
    - nodes.c: File that contains all of the node creations of different data types that need to be compiled to run
    - controlFlow.c: File that contains the control flow for the hunters and ghosts which are used by threads that need to be compiled to run
    - util.c: File that contains the code of helper functions that help with printing and retrieving random numbers that need to be compiled to run
    - defs.h: File that contains function forward declarations and definitions
    - Makefile: File to compile and create executables along with cleaning them up 
    - README.txt: File purpose is to provide the user with some information about this program's purpose and how to use it

Compiling and Executing:
    1. Navigate to the folder containing the source files in the terminal
    2. Use the command `make all` to create the file `ACGame` which can be executed
    3. Use the command `./ACGame` while in the folder that contains the executable to run the program
    

Operating instructions:
    When program is running follow the given prompts to enter the names of the hunters and watch the game play out 