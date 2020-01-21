# Hangman
  O  
\ | /  
 / \  


## Members 
- Kenneth Chin (PD4)
- Minuk Kim  (PD4)
- Derek Lao  (PD4)

## Description of Project  
We are making our attempt of creating the popular child's game hangman.
The objective of the game is to guess a word that sthe computer randomly generates. The
guessers guess a letter each turn. If the letter is part of the word, the
position the letter is in the word is shown, else a part of a drawing of a stick
figure is drawn (representative of certain number of lives). Our game is two players so each 
player will take turns guessing, who ever guess first wins!

## Technical Design:
- Working with files: Obtain word from text file to be used for the game
- Semaphores: During a player's turn, prevents the other player from making a move.
- Shared memory: Players share the letters that have been guessed, the progress on guessing the word, 
how the word they are guessing for, and whether the game has ended
- Signals: As a safety measure, SIGINT is prevented from immediately exiting the program and
formally exiting the program is encouraged
- Processes: We use processes to fork and exec "clear"
- Allocating memory: Used to calloc for parse_args() in order to process the "clear" command


## How to run
To run our project, open two terminal windows/tabs. Then run the program on both
terminals. Instructions on how to play will be displayed. Take turns guess the
word against another player, and try to guess it before they do!


## Resources
We used a txt file to store our words taken from Github user Xethron which can be found here:  
'https://github.com/Xethron/Hangman/blob/master/words.txt'
It has been slightly modified.
