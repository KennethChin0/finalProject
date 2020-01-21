# Hangman
  O  
/ | \  
 / \  


## Members 
- Kenneth Chin (PD4)
- Minuk Kim  (PD4)
- Derek Lao  (PD4)

## Description of Project  
We are making our attempt of creating the popular child's game hangman.
The objective of the game is to guess a word that the computer randomly generates. The
guessers guess a letter each turn. If the letter is part of the word, the
position the letter is in the word is shown, else a part of a drawing of a stick
figure is drawn (representative of certain number of lives). 
Our game is two players so each player will take turns guessing, the player to guess 
the word first or run out of lives last wins.

But there is a twist! During their turns, players only have 3 seconds per turn to
view the word bank and the progress on guessing the word.

## Technical Design:
- Working with files: Obtain word from text file to be used for the game
- Semaphores: During a player's turn, prevents the other player from making a move.
- Shared memory: Players share the letters that have been guessed, the progress on guessing the word, 
how the word they are guessing for, and whether the game has ended
- Signals: As a safety measure, SIGINT is prevented from exiting the program and
formally exiting the program is encouraged. Instead, SIGINT is used to skip waiting times
SIGQUIT is allowed to be used to force exit the program when pressed 3 times, 
but this is discouraged as it may break the program and necessitate the Disaster Protocol
- Processes: We use processes to fork and exec "clear"
- Allocating memory: Used to calloc for parse_args() in order to process the "clear" command

## How to run the project:
To run our project, open two terminal windows/tabs. Then run the program on both
terminals. Instructions on how to play will be displayed. Take turns guess the
word against another player, and try to guess it before they do!

## Disaster Protocol - What to do if the project breaks:
You can not simply recompile the project if the program exited abnormally,
because there will be shared memory and semaphores that need to be removed.
In order to remove them, follow the Disaster Protocol printed at the top of the terminal
while the game is running. A copy of it is here:

Disaster Protocol:
1. All players press Control + C until they reach the guessing screen.
2. All players type "exit" for their guess to exit their programs.
3. Recompile the program using the following steps:  
     a. Type "make clean"  
     b. Type "make"  
     c. Type "make run"  
* dummy line

## Resources
We used a txt file to store our words taken from Github user Xethron which can be found here:  
'https://github.com/Xethron/Hangman/blob/master/words.txt'
It has been slightly modified.
