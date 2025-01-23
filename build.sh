#!/bin/bash

# Kompiliere Hangman
echo "Kompiliere Hangman..."
gcc -std=c99 -Wall -Wextra -pedantic -Wno-unused-parameter hangman.c -o hangman.sh
if [ $? -ne 0 ]; then
    echo "Fehler beim Kompilieren von Hangman!"
    exit 1
fi