# Wordle

An attempt at making a command line wordle game.

The program will select a random word from the dictionary (solutions.txt), output a title Wordle and the instructions for how to interpret the colors in the game, and then ask the user for input for the guess at the word. The program will them output each letter in the guess with either green, yellow, or white font to show that the letter is in the correct place, in the word but in the wrong place, or not in the word respectively. If you guess the word in 6 attempts or less, it will output a congratulatory message, or if you do not guess the game, it will exit and output a slightly sadder message.

The code is organized into two files, a header and the main C++ file. The header contains all the necessary functions to run the game, and the main wordle.cpp file calls all the functions to output on the command line.

The program assumes that the use has access to the algorithm, 
ctime, fstream, iomanip, iostream, random, string, and vector libraries. It also uses one command "cls" from the windows command line, but still runs on other machines.