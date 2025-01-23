\mainpage README
# Hangman Game in C

This is a simple implementation of the classic Hangman game in C. The game allows the user to guess a word letter by letter, with a limited number of attempts. The game also logs all actions and outputs to a file for later review.

## Compilation
	starting the programm with run.sh will start with the word Katze, if you prefer another word read the README-file.
    	you will build the programm with the build.sh file.
	This will compile the .c file using "gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter"
	and automaticly execute the file in its normal mode.

## Features

- **Random Word Selection**: The game can select a random word from a file containing a list of words.
- **Logging**: All game actions, including guesses, correct/incorrect attempts, and game state, are logged to a file (`game_log.txt`).
- **Hangman Visualization**: The game displays the hangman's gallows and updates it based on the number of remaining attempts.
- **Word Reset**: The game can reset the status of words in the word list file, allowing words to be reused in future games.
- **Input Validation**: The game ensures that only valid letters are entered as guesses.

## Requirements

- **C Compiler**: A C compiler such as `gcc` is required to compile the code.
- **Word File**: A text file containing words to be used in the game. Each word should be prefixed with a status (0 or 1) and separated by a comma (e.g., `0,apple`).
A word file is given by us but you could also create your own.

## Run the Game
   ```bash
   ./hangman <word>
   ```
   Replace `<word>` with the word you want to guess. Alternatively, you can provide a file path to a word list when prompted.

3. **Follow the Prompts**:
   - The game will prompt you to guess letters.
   - You can continue playing multiple rounds or exit the game.

## File Format for Word List

The word list file should contain words in the following format:
```
0,apple
0,banana
0,cherry
```
- `0` indicates that the word is available for selection.
- `1` indicates that the word has been used and is not available for selection.

## Example Usage

1. **Start the Game**:
   ```bash
   ./hangman apple
   ```

2. **Guess Letters**:
   ```
   Welcome to hangman!
   The word to guess is: _ _ _ _ _ (5 letters)
   Round 1:
   Guess a letter: a
   Correct! The word so far: a _ _ _ _
   Letters not in my word: 
   ```

3. **Continue or Exit**:
   ```
   Do you want to continue playing? (y or n): y
   Enter the path to the file containing words: words.txt
   ```

4. **Reset Word Status**:
   ```
   Do you want to reset the state of the words? (y or n): y
   All status values have been reset to 0.
   Thanks for playing!
   ```