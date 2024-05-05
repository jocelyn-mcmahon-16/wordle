#ifndef WORDLE_H
#define WORDLE_H

#include <algorithm>
#include <cctype>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>

const int word_length = 5;
const int NOT_MATCH = 0;
const int PARTIAL_MATCH = 1;
const int MATCH = 2;
const int num_guesses = 6;


std::string chooseSolution() { //was getRandomWord
    std::vector<std::string> out;
    std::vector<std::string> solutions;
    std::ifstream file ("solutions.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.length() == word_length){
            solutions.push_back(line);
        }
    }
    
    // this is what I want! Now just need help updating g++ so I can run it
    // std::sample(solutions.begin(), solutions.end(), std::back_inserter(out), 1, std::mt19937{std::random_device{}()});
    // std::string solution = out[0];

    // seed rng
    // this is the only one so far that is giving me a different solution every time, but it just essentially runs through the words in alphabetical order...
    srand(time(NULL));    
    int solution_value = std::rand() % solutions.size();

    std::string solution = solutions[solution_value];
    return solution;
}

void raiseCase(std::string &guess) {
    std::transform(guess.begin(), guess.end(), guess.begin(), [](unsigned char c)
    { return std::toupper(c); });
}

bool isValid(std::string solution) {  //was isValid
    // TODO check solution correctness from API (e.g. WordsAPI)
    return solution.length() == word_length && solution.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == std::string::npos;
}

void checkGuess(std::vector<std::vector<int>> &matches, int tryIndex, std::string solution, std::string guess) { // was markMatch
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


bool isAllMatch(std::string solution, std::string guess) { // was isAllMatch
    for (int i = 0; i < guess.length(); i++) {
        if (guess[i] != solution[i])
            return false;
    }
    return true;
}


void startGame(std::vector<std::string> tries, std::vector<std::vector<int>> matches, int attempt) { // was printWordle
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

void printGuesses(std::vector<std::string> tries, std::vector<std::vector<int>> matches, int attempt) { // this is a new funciton I separated out
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