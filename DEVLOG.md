# Hangman Dev Log
## Kenneth Chin, Derek Lao, Minuk Kim
Systems PD4

Kenneth -- 2020-1-02 22:50:
Initialized repo, linked submodule, created readme, started proposal FILE

Kenneth -- 2020-1-09 10:45:
Started a template for hangman project, created lives and words.txt file

Minuk -- 2020-1-09:
Wrote the function placeholder with proper parameters

Kenneth -- 2020-1-12 11:00:
Made simple hangman to work (the basics)
-guessing
-randomly selected word
-determining winner and loser

Derek -- 2020-1-14 10:22:
Corrected draw() code to make the person draw more like a person

Derek -- 2020-1-14 12:35:
Implemented screen clear and reset after each letter is guessed

Kenneth -- 2020-1-15 19:23:
Tried to make a wordbank for the words that are already guessed

Derek -- 2020-1-18 20:20:
Very simple shared memory implemented with the answer

Minuk -- 2020-1-19:
Started to work on a better interface using ncurses library

Derek -- 2020-1-20 01:52:
Shared memory implemented in checking progress for guessing word

Derek -- 2020-1-20 03:08:
Semaphore-mediated turn-taking implemented, but breaks too easily from "Control+C"
induced SIGINT

Derek -- 2020-1-20 05:12:
Created sighandler function to catch SIGINT and warn player before exiting.
Also it just so happens that SIGINT can be used to exit out of
semaphore-induced turn waiting.

Derek -- 2020-1-20 19:20:
Shared memory implemented with guessing a random word for the answer

Derek -- 2020-1-20 21:06:
Every time a letter is guessed, the player can see their lives and word bank

Minuk -- 2020-1-20:
Created DEVLOG and formatted it.

Derek -- 2020-1-20 21:15:
Added print statements for player instructions in the event of disaster

Derek -- 2020-1-20 22:34:
Time-limited viewing to word-guessing progress and word bank implemented

Kenneth -- 2020-1-20 22:50:
Minor fixes to bugs and small things such as print statements and spacing

Derek -- 2020-1-20 23:34:
Win and lose statements finished
