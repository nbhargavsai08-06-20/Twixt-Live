Twixt – CLI Version

Name    : NALLAMALA BHARGAV SAI 
Roll.No : 2025102032
Section : B


CLI Commands:

place r c     Place a peg at row r, column c (autolink enabled)
done          End your turn (must place a peg first)
help          Show command list
quit          Exit the game

Folder Structure:
|
|-- game.c       
|-- main.c        
|-- README.md      
|-- Makefile
|-- twixt.h  

Compilation Instructions:

If using Makefile:

make

Run the program:
./twixt

If compiling manually:

gcc main.c game.c -o twixt -std=c11 -Wall -Wextra
./twixt

THANK YOU .....