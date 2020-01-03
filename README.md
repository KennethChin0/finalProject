# Hangman
  O  
\ | /  
 / \  


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
- There will be an option to play single player or two player.  
- The computer generates a random word / phrase and the players will take turns guessing.  
- Using the terminal, the player is given 6 lives, represented by a picture.


## Technical Design:
- Working with files: We plan on storing the words and phrases generated by the computer in a txt file.
- Networking: When the two player option is chosen, we plan on using networking to allow the players to take turn guessing.
- Signals: To relay the guess between two guesses.
- Processes: We need to fork new processes to allow the player to have multiple turns.

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
January 6 - Get hangman versus the computer down. (Basic Functions)  Part 1

January 8 - Get hangman versus the computer down. (Basic Functions) Part 2

January 10 - Add networking portion (2 player mode)

January 13 - Implement any extra features / check for errors/mistakes

January 16/17 - Submit!
