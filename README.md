# Hangman

## Members
- Kenneth Chin  
- Minuk Kim  
- Derek Lao  

## Description of Project  
We are making our attempt of creating the popular child's game hangman.
The objective of the game is to guess a word that someone else chooses. The
guessers guess a letter each turn. If the letter is part of the word, the
position the letter is in the word is shown, else a part of a drawing of a stick
figure is drawn (representative of certain number of lives). Other aspects of graphics will be implemented to look more interactive and
If the guesser can get the word before the drawing is done, they win.

## Description of User Interface:  
- There is an option to choose to be the guesser or chooser.
- For guessers - there will be an option to guess a letter or word.
- For chooser - they will be able to input their word


## Technical Design:
- Allocated Memory: Store the words and guess letters.
- Networking: Allow two (or more tbd) players to play against each other.
- Signals: To relay the what letters the guessers guess and what the word is.
- Share Memory/ Semaphores: Only one guesser can go at a time.

## Project Breakdown:
#### Part 1:
- Finish implementing the entering of letters into a space displayed on the terminal, using user input from the keyboard.

- Implement a checking method for the system to check entered letter against a letter.

- Implement checking method for system to check entered letter against all the letters in the word.

- Implement a method to remove all the letters from the word that have been matched, leaving the remainder of letters that have not been matched yet still in the data structure containing all the letters.

#### Part 2:

- Have a counter for number of wrong letters a user has guessed.

- Draw victim progressively based on the number of wrong letters.

#### Part 3:

- Networking

## Timeline:
January 6 - Figure out networking/ get communication between 2 players.  

January 10 - Make basic functions of hangman on one computer.

January 13 - Create multiplayer using networking

January 15 - Add extra features / make sure everything working

January 16/17 - Submit!
