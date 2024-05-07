#ifndef WORDLE_H
#define WORDLE_H

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

const int word_length = 5;
const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;
const int num_guesses = 6;

///
/// a function to choose one random word from options read in from a text file
/// no required input
/// reads in the words in solutions.txt, our dictionary file, line by line into the vector solutions
/// we seed a basic rng with the time, which then chooses an index from the number of elements in our solutions vector
/// we then choose that indexed string as the solution to the game
/// returns a string, solution
///
std::string chooseSolution() {
    std::vector<std::string> solutions;
    std::ifstream file ("solutions.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.length() == word_length){
            solutions.push_back(line);
        }
    }
    
    // std::sample(solutions.begin(), solutions.end(), std::back_inserter(out), 1, std::mt19937{std::random_device{}()});
    // std::string solution = out[0];

    // seed rng
    srand(time(NULL));    
    int solution_value = std::rand() % solutions.size();
    std::string solution = solutions[solution_value];
    return solution;
}

///
/// raises the case of a string
/// requires input of a reference to a string
/// uses the transform and toupper functions to raise each letter in a given guess to its uppercase version based on the char value
/// returns the uppercase letter
///
void raiseCase(std::string &guess) {
    std::transform(guess.begin(), guess.end(), guess.begin(), [](unsigned char c)
    { return std::toupper(c); });
}

///
/// checks to make sure a guess is all letters
/// input is any string
/// checks to ensure the length is correct (5), and that the word does not include any characters except alphabetic in our input
/// returns 1 (true) or 0 (false)
///
bool isValid(std::string solution) {
    return solution.length() == word_length && solution.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

///
/// finds if the letters in the given guess match any letters in the solution
/// input is a reference to the vector holding the values associated with if the letter has a match, and two strings: the solution and a given guess
/// loops over the letters and compares the char values of each to check if it is not a match
/// if not not a match, it loops to check if the placement of the letters is the same to confirm a partial or (total) match
/// updates the matches vector
///
void checkGuess(std::vector<std::vector<int>> &matches, int tryIndex, std::string solution, std::string guess) {
    for (int i = 0; i < guess.length(); i++) {
        matches[tryIndex][i] = NOT_MATCH;
    }
    for (int j = 0; j < guess.length(); j++) {
        for (int i = 0; i < solution.length(); i++) {
            if (guess[j] == solution[i]) {
                if (i == j) {
                    matches[tryIndex][j] = MATCH;
                   break;
                } else {
                    matches[tryIndex][j] = PARTIAL_MATCH;
                }
            }
        }
    }
}

///
/// special case for if the whole word is a match
/// inputs are the strings solution and guess
/// loops over each letter to see if the words are not totally equal, if true, guess matches solution
/// returns 1 (true) or 0 (false)
///
bool isAllMatch(std::string solution, std::string guess) {
    for (int i = 0; i < guess.length(); i++) {
        if (guess[i] != solution[i])
            return false;
    }
    return true;
}

///
/// clears the screen for windows command line and outputs the Wordle title card
/// no reqiured input
/// just outputs these fun lines
///
void startGame() {
    system("cls");
    std::cout << "=================================================================" << std::endl;
    std::cout << "|                                                               |" << std::endl;
    std::cout << "|   $$\\      $$\\                           $$\\ $$\\              |" << std::endl;
    std::cout << "|   $$ | $\\  $$ |                          $$ |$$ |             |" << std::endl;
    std::cout << "|   $$ |$$$\\ $$ | $$$$$$\\   $$$$$$\\   $$$$$$$ |$$ | $$$$$$\\     |" << std::endl;
    std::cout << "|   $$ $$ $$\\$$ |$$  __$$\\ $$  __$$\\ $$  __$$ |$$ |$$  __$$\\    |" << std::endl;
    std::cout << "|   $$$$  _$$$$ |$$ /  $$ |$$ |  \\__|$$ /  $$ |$$ |$$$$$$$$ |   |" << std::endl;
    std::cout << "|   $$$  / \\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |$$   ____|   |" << std::endl;
    std::cout << "|   $$  /   \\$$ |\\$$$$$$  |$$ |      \\$$$$$$$ |$$ |\\$$$$$$$\\    |" << std::endl;
    std::cout << "|   \\__/     \\__| \\______/ \\__|       \\_______|\\__| \\_______|   |" << std::endl;
    std::cout << "|                                                               |" << std::endl;
    std::cout << "=================================================================" << std::endl;
}

///
/// outputs the instructions
/// no required input
/// prints out the instructions for the wordle game, with color coding
///
void printInstructions() {
    std::cout << "Welcome to Wordle!" << std::endl;
    std::cout << "You have 6 attempts to guess a 5 letter word. Once you have made a guess," << std::endl;
    std::cout << "letters that are not in the word will be printed in WHITE, \nletters in the word but not in the correct position will be printed in \033[33mYELLOW\033[0m, \nand letters that are in the correct position will be printed in \033[32mGREEN\033[0m." << std::endl;
    std::cout << "Enter a guess to start the game or type Q to quit: " << std::endl;
}

///
/// outputs the guesses centered in boxes
/// input a vector of strings containing each guess (tries), a vector of vectors containing the matches data, and the number of attempts
/// creates the boxes by combining the seperator, padding, and text lines
/// also assigns the colors to the letters as needed depending on their match status
/// outputs a nice set of boxes with the color coded letters from the user's guess
/// will output all the rows for each of the guesses, not just the most recent, to allow the user to see their previous guesses
///
void printGuesses(std::vector<std::string> tries, std::vector<std::vector<int>> matches, int attempt) {
    for (int i = 0; i <= attempt && i < tries.size(); i++) {
        std::string separator = "-";
        std::string padding = "|";
        std::string text = "|";
        for (int j = 0; j < tries[i].length(); j++) {
            separator += "------";
            padding += "     |";
            char value = std::toupper(tries[i][j]);
            text += "  ";
            if (matches[i][j] == PARTIAL_MATCH) {
                text += "\033[33m";
            } else if (matches[i][j] == MATCH) {
                text += "\033[32m";
            }
            text += value;
            if (matches[i][j] == PARTIAL_MATCH || matches[i][j] == MATCH) {
                text += "\033[0m";
            }
            text += "  |";
        }
        if (i == 0) { 
            std::cout << separator << std::endl;
        }
        std::cout << padding << std::endl;
        std::cout << text << std::endl;
        std::cout << padding << std::endl; 
        std::cout << separator << std::endl;
    }
}

///
/// checks the number of attempts to know what message to congratulate you with
/// inputs the attempt number, and the strings solution and guess
/// uses the switch statement to move between cases depending on the number of attempts, each with a unique congratulatory message if you have guessed the solution
/// if you didn't guess the solution, outputs a slightly sadder consolation message and tells you what the solution was
///
void checkAttempts(int attempt, std::string solution, std::string guess) {
    if (guess == solution) {
        switch (attempt) {
            case 1:
                std::cout << "Genius" << std::endl;
                break;
            case 2:
                std::cout << "Magnificent" << std::endl;
                break;
            case 3:
                std::cout << "Impressive" << std::endl;
                break;
            case 4:
                std::cout << "Splendid" << std::endl;
                break;
            case 5:
                std::cout << "Great" << std::endl;
                break;
            case 6:
                std::cout << "Phew" << std::endl;
                break;
        }
    } else if (guess != solution && attempt == 6) {
        std::cout << "The word was: " << solution << std::endl;
    }
}

#endif