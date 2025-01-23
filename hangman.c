#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/**
 * \file hangman.c
 * \author Ömer GÜNER(ic24b071)
 * \brief This is the main file for the Hangman game.
 */

/**
 * \brief Generates the name of the log file using the current date and time.
 * \brief used referense code : //source : https://stackoverflow.com/questions/26900122/c-program-to-print-current-time
 * \param logFileName The buffer to store the generated log file name.
 * \param size The size of the buffer.
 */
void log_current_time(FILE *logginfile) {
    time_t current_time = time(NULL);
    char *time_string = ctime(&current_time);  
    fprintf(logginfile, "Current Time: %s", time_string);
}

// func für The word to guess is: _ _ _ _ _ _ _ _ _ _ (n letters)
//size_t wird verwendet, weil man jede Möglichkeit bedecken will und nicht weißt wie groß die variable wird.
/**
 * \brief Displays the word to guess with underscores for unguessed letters.
 *  //! func für The word to guess is: _ _ _ _ _ _ _ _ _ _ (n letters)
 *  //!size_t wird verwendet, weil man jede Möglichkeit bedecken will und nicht weißt wie groß die variable wird.
 * \param word The word to guess.
 * \param length The length of the word.
 */
void display_word_to_guess(char *word, size_t length) {
    printf("The word to guess is: ");
    for (size_t i = 0; i < length; i++) {
        printf("_ ");
    }
    printf("(%zd letters)\n", length);
}

/**
 * \brief Compares the guessed letter with the word and updates the game state.
 * //! func was einzelne buchstaben vergleicht und wenn ein ganzes wort eingeben wird vergleicht sie die beide strings mit string compare
 * \param length Length of the word.
 * \param guess The guessed letter.
 * \param array The word to guess.
 * \param round Pointer to the current round number.
 * \param attempts Pointer to the remaining attempts.
 * \param wordsofar Array representing the current state of guessed letters.
 * \param false Array of letters not in the word.
 * \return Result of the comparison (0 = incorrect, 1 = correct, 2 = word complete, 3 = already guessed).
 */
int vergleich_guess_mit_word(int length, char guess, const char *array, int *round, int *attempts, char *wordsofar, char *false) {
    int gefunden = 0;
//!https://www.geeksforgeeks.org/strchr-in-c/
    if (strchr(wordsofar, guess) != NULL || strchr(false, guess) != NULL) {
        return 3;
    }

    for (int i = 0; i < length; i++) {
        if (array[i] == guess && wordsofar[i] == '_') {
            wordsofar[i] = guess;
            gefunden = 1;
        }
    }

    if (strcmp(wordsofar, array) == 0) {
        return 2;
    }

    if (gefunden) {
        (*round)++;
        return 1;
    } else {
        int false_length = strlen(false);
        if (false_length > 0) {
            false[false_length] = ',';
            false_length++;
        }
        false[false_length] = guess;
        false[false_length + 1] = '\0';

        (*attempts)--;
        (*round)++;
        return 0;
    }
}

/**
 * \brief Selects a random word from a file.
 * \param file Pointer to the file containing the words.
 * \param array_word Array to store the selected word.
 * \return Pointer to the selected word, or NULL if no word is found.
 */
char *select_random_wort(FILE *file, char array_word[]) {
    char continue_word[100] = {0};
    int status_numb;
    int count = 0;

    rewind(file);

    while (fscanf(file, "%d,%99s", &status_numb, continue_word) == 2) {
        if (status_numb == 0) {
            count++;
        }
    }

    if (count == 0) {
        printf("Error: No available words found in the file.\n");
        return NULL;
    }

    srand(time(NULL));
    int random_line = rand() % count;

    rewind(file);

    int temp_line = 0;
    while (fscanf(file, "%d,%99s", &status_numb, continue_word) == 2) {
        if (status_numb == 0) {
            if (temp_line == random_line) {
                strcpy(array_word, continue_word);
                //https://stackoverflow.com/questions/76245752/what-is-the-use-of-zero-offset-in-fseek-function-with-seek-cur
                fseek(file, -strlen(continue_word) - 2, SEEK_CUR);
                fprintf(file, "1,%s", continue_word);
                return array_word;
            }
            temp_line++;
        }
    }

    printf("Error: Could not find a random word.\n");
    return NULL;
}

/**
 * \brief Validates that the input consists only of letters.
 * \param guess The input to validate.
 * \return 1 if the input is valid, 0 otherwise.
 */
int nur_letter(char guess[]) {
    for (size_t i = 0; i < strlen(guess); i++) {
        if (!isalpha(guess[i])) {
            return 0;
        }
    }
    return 1;
}

/**
 * \brief Displays the hangman's gallows based on the number of attempts left.
 * \param logfile Pointer to the log file.
 * \param attempts Pointer to the remaining attempts.
 * \param word The word to guess.
 */
void func_galge(FILE *logfile, int *attempts, char *word){
            if (*attempts == 9) {
            printf("=========\n");
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,"=========\n");
        } else if (*attempts == 8) {
            printf(
                "    |\n"
                "    |\n"
                "    |\n"
                "    |\n"
                "    |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "    |\n"
                "    |\n"
                "    |\n"
                "    |\n"
                "    |\n"
                "=========\n"
            );
        } else if (*attempts == 7) {
            printf(
                "  +---+\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );            
        } else if (*attempts == 6) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );            
        } else if (*attempts == 5) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );            
        } else if (*attempts == 4) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
        } else if (*attempts == 3) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|   |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|   |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );            
        } else if (*attempts == 2) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                "      |\n"
                "      |\n"
                "=========\n"
            );            
        } else if (*attempts == 1) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " /    |\n"
                "      |\n"
                "=========\n"
            );
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " /    |\n"
                "      |\n"
                "=========\n"
            );
        } else if (*attempts == 0) {
            printf(
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " / \\  |\n"
                "      |\n"
                "=========\n"
            );
            printf("Game over! The word was: %s\n", word);
            log_current_time(logfile);
            fprintf(logfile,"\n");
            fprintf(logfile,
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " / \\  |\n"
                "      |\n"
                "=========\n"
            );
            fprintf(logfile,"Game over! The word was: %s\n", word);
        }
}
/**
 * \brief Handles the main game loop, including user input and game state updates.
 * \param length Length of the word.
 * \param word The word to guess.
 * \param wordsofar Array representing the current state of guessed letters.
 * \param falsewordsofar Array of letters not in the word.
 * \param round Pointer to the current round number.
 * \param attempts Pointer to the remaining attempts.
 * \param logfile Pointer to the log file.
 */
void func_outputs(int length, char *word, char *wordsofar, char *falsewordsofar, int *round, int *attempts, FILE *logfile) {
    display_word_to_guess(word, length);
    while (*attempts > 0) {
        printf("Round %d:\n", *round);
        fprintf(logfile, "Round %d:\n", *round);
        printf("Guess a letter: ");
        fprintf(logfile, "Guess a letter: ");
        char guess[100];
        scanf(" %99s", guess);
        fprintf(logfile, "%s\n", guess);

        int istwort = nur_letter(guess);

        for (size_t i = 0; i < strlen(guess); i++) {
            guess[i] = tolower(guess[i]);
        }

        if (strlen(guess) == 1 && istwort == 1) {
            int ergebnis = vergleich_guess_mit_word(length, guess[0], word, round, attempts, wordsofar, falsewordsofar);

            if (ergebnis == 1) {
                printf("Correct! The word so far: %s\n", wordsofar);
                printf("Letters not in my word: %s\n", falsewordsofar);
                log_current_time(logfile);
                fprintf(logfile, "Correct! The word so far: %s\n", wordsofar);
                fprintf(logfile, "Letters not in my word: %s\n", falsewordsofar);
            } else if (ergebnis == 0) {
                printf("Incorrect! You have %d attempts left.\n", *attempts);
                printf("The word so far: %s\n", wordsofar);
                printf("Letters not in my word: %s\n", falsewordsofar);
                log_current_time(logfile);
                fprintf(logfile, "Incorrect! You have %d attempts left.\n", *attempts);
                fprintf(logfile, "The word so far: %s\n", wordsofar);
                fprintf(logfile, "Letters not in my word: %s\n", falsewordsofar);
            } else if (ergebnis == 2) {
                printf("Congratulations! You've guessed the word: %s!\n", wordsofar);
                printf("Letters not in my word: %s\n", falsewordsofar);
                log_current_time(logfile);
                fprintf(logfile, "Congratulations! You've guessed the word: %s!\n", wordsofar);
                fprintf(logfile, "Letters not in my word: %s\n", falsewordsofar);
                break;
            } else if (ergebnis == 3) {
                printf("You already guessed that or tried it!!\n");
                printf("The word so far: %s\n", wordsofar);
                printf("Letters not in my word: %s\n", falsewordsofar);
                log_current_time(logfile);
                fprintf(logfile, "You already guessed that or tried it!!\n");
                fprintf(logfile, "The word so far: %s\n", wordsofar);
                fprintf(logfile, "Letters not in my word: %s\n", falsewordsofar);
            }
        } else if (strcmp(guess, word) == 0) {
            printf("Congratulations! You've guessed the word: %s!\n", word);
            log_current_time(logfile);
            fprintf(logfile, "Congratulations! You've guessed the word: %s!\n", word);
            break;
        } else if (istwort == 0) {
            printf("Invalid entry! Please make sure to use letters.\n");
            log_current_time(logfile);
            fprintf(logfile, "Invalid entry! Please make sure to use letters.\n");
            continue;
        } else {
            printf("Wrong guess! Game over! The word was: %s\n", word);
            log_current_time(logfile);
            fprintf(logfile, "Wrong guess! Game over! The word was: %s\n", word);
            break;
        }
        func_galge(logfile, attempts, word);
    }
}
/**
 * \brief Resets the status of all words in the word list file to 0.
 * \param file Pointer to the file containing the words.
 */
void reset_all_status(FILE *file) {
    char continue_word[100] = {0};
    int status_numb;
    long current_pos;

    rewind(file);

    while (fscanf(file, "%d,%99s", &status_numb, continue_word) == 2) {
        current_pos = ftell(file);
        if (status_numb == 1) {
            fseek(file, current_pos - strlen(continue_word) - 2, SEEK_SET);
            fprintf(file, "0,%s", continue_word);
            fseek(file, current_pos, SEEK_SET);
        }
    }

    printf("All status values have been reset to 0.\n");
}
/**
 * \brief The main function to run the Hangman game.
 * \param argc Number of command-line arguments.
 * \param argv Array of command-line arguments.
 * \return 0 on successful execution, 1 on error.
 */
int main(int argc, char *argv[]) {
    // Log-Datei öffnen
    FILE *logfile = fopen("game_log.txt", "a");
    if (logfile == NULL) {
        printf("Fehler beim Öffnen der Log-Datei!\n");
        return 1;
    }
    fprintf(logfile, "Game start:");
    log_current_time(logfile);

    // Überprüfung der Eingabe
    if (argc < 2) {
        printf("Bitte geben Sie das Wort zum Raten ein!\n");
        fclose(logfile);
        return 1;
    }

    int istwort = nur_letter(argv[1]);
    if (istwort == 0) {
        printf("Invalid character! Please only use words and no special characters or integers!\n");
        fclose(logfile);
        return 1;
    }

    char *dasWort = argv[1];
    int wordlength = strlen(dasWort);

    char array_word[wordlength + 1];
    strcpy(array_word, dasWort);
    for (int i = 0; i < wordlength; i++) {
        array_word[i] = tolower(dasWort[i]);
    }
    fprintf(logfile, "Das eingegebene Wort: %s\n", array_word);

    // Speicher für das Spiel initialisieren
    int temp_round = 1;
    int temp_attempts = 10;
    int *round = &temp_round;
    int *attempts = &temp_attempts;

    char *array_wordsofar = calloc((wordlength + 1), sizeof(char));
    if (array_wordsofar == NULL) {
        printf("Memory allocation failed!\n");
        fclose(logfile);
        return 1;
    }
    memset(array_wordsofar, '_', wordlength);
    array_wordsofar[wordlength] = '\0';

    char *false_wordsofar = calloc(2 * (wordlength + 1), sizeof(char));
    if (false_wordsofar == NULL) {
        printf("Memory allocation failed!\n");
        free(array_wordsofar);
        fclose(logfile);
        return 1;
    }

    printf("Welcome to hangman!\n");
    fprintf(logfile,"Welcome to hangman!\n");
    func_outputs(wordlength, array_word, array_wordsofar, false_wordsofar, round, attempts, logfile);

    while (getchar() != '\n');
    char nextround;
    while (1) {
        printf("Do you want to continue playing? (y or n): ");
        scanf(" %c", &nextround);
        printf("\n");

        nextround = tolower(nextround);

        if (nextround == 'y' || nextround == 'n') {
            break;
        } else {
            printf("Invalid entry, please type in y or n!\n");
        }
    }

    log_current_time(logfile);
    fprintf(logfile, "Do you want to continue playing? (y or n): %c\n", nextround);

    if (nextround == 'y') {
        printf("Continuing to the next round...\n");
        fprintf(logfile, "Continuing to the next round...\n");
    } else if (nextround == 'n') {
        printf("Thanks for playing!\n");
        log_current_time(logfile);
        fprintf(logfile, "Thanks for playing!\n");
        free(array_wordsofar);
        free(false_wordsofar);
        fclose(logfile);
        return 0;
    }

    // Nächste Runde mit zufälligem Wort
    nextround = tolower(nextround);
    while (getchar() != '\n');

    char filename[256];
    printf("Enter the path to the file containing words: ");
    scanf("%255s", filename);
    log_current_time(logfile);
    fprintf(logfile, "Enter the path to the file containing words: %s\n", filename);

    FILE *fptr_word = fopen(filename, "r+");
    if (!fptr_word) {
        printf("Opening the file did not work!!!\n");
        free(array_wordsofar);
        free(false_wordsofar);
        fclose(logfile);
        return 1;
    }

    do {
        char nextround_word[100] = {0};
        select_random_wort(fptr_word, nextround_word);
        if (!select_random_wort(fptr_word, nextround_word)) {
            printf("No available words found in the file.\n");
            break;
        }

        int next_wordlength = strlen(nextround_word);
            memset(array_wordsofar, '_', next_wordlength);
            array_wordsofar[next_wordlength] = '\0';
            memset(false_wordsofar, 0, 11); // Setze false_wordsofar zurück
            *attempts = 10;
            *round = 1;
        func_outputs(next_wordlength, nextround_word, array_wordsofar, false_wordsofar, round, attempts, logfile);

        if (nextround == 'y') {
            memset(array_wordsofar, '_', next_wordlength);
            array_wordsofar[next_wordlength] = '\0';
            memset(false_wordsofar, 0, 11); // Setze false_wordsofar zurück
            *attempts = 10;
            *round = 1;
        }

        while (getchar() != '\n');

        while (1) {
            printf("Do you want to continue playing? (y or n): ");
            scanf("%c", &nextround);
            printf("\n");
            nextround = tolower(nextround);
            if (nextround == 'y' || nextround == 'n') {
                break;
            } else {
                printf("Invalid entry, please type in y or n!\n");
            }
        }

        log_current_time(logfile);
        fprintf(logfile, "Do you want to continue playing? (y or n): %c\n", nextround);

        char reset_wordlist;

        while (getchar() != '\n');
        if (nextround == 'n') {
            while (1) {
                printf("Do you want to reset the state of the words? (y or n): ");
                scanf("%c", &reset_wordlist);
                printf("\n");
                fprintf(logfile, "Do you want to reset the state of the words? (y or n): %c\n", reset_wordlist);
                reset_wordlist = tolower(reset_wordlist);
                if (reset_wordlist == 'y' || reset_wordlist == 'n') {
                    break;
                } else {
                    printf("Invalid entry, please type in y or n!\n");
                }
            }
            if (reset_wordlist == 'y') {
                reset_all_status(fptr_word);
            }
            printf("Thanks for playing!\n");
            log_current_time(logfile);
            fprintf(logfile, "Thanks for playing!\n");
            break;
        }
    } while (nextround == 'y');

    fprintf(logfile, "Game end:\n");
    log_current_time(logfile);

    free(array_wordsofar);
    free(false_wordsofar);
    fclose(logfile);
    fclose(fptr_word);

    return 0;
}