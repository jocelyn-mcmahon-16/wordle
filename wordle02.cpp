#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <Windows.h>
#include "wordle02.H"

int main() { //int, char **) {
    
    const int word_length = 5;
    const int NOT_MATCH = 0;
    const int PARTIAL_MATCH = 1;
    const int MATCH = 2;
    const int num_guesses = 6;
    int attempts = 6;

    std::string guess;
    int attempt = 0;



    std::cout << attempt << std::endl;



    std::vector<std::string> tries(attempts);    
    std::vector<std::vector<int>> matches(attempts, std::vector<int>(word_length));

    // this step is what's fucking up
    std::string solution = chooseSolution(); //was getRandomWord
    raiseCase(solution); // was toUpperCase
    std::cout << solution << std::endl;


    std::cout << attempts << std::endl;



    // startGame(tries, matches, attempt);  // was printWordle

    // while (attempt < attempts) {
    //     do {
    //         std::cout << "Enter your guess (word length must be " + std::to_string(word_length) + ") or type Q to quit: ";
    //         std::getline(std::cin, guess);
    //         raiseCase(guess);
    //     } while (guess != "Q" && !isValid(guess));
    //     if (guess == "Q") {
    //         std::cout << "Quit game" << std::endl;
    //         break;
    //     }
    //     tries[attempt] = guess;
    //     attempt++;
    // }

    // std::cout << attempts +1 << std::endl;

    // checkGuess(matches, attempt, solution, guess);

    // if (isAllMatch(solution, guess)) {
    //     std::cout << "Found the word" << std::endl;
    //     checkAttempts(attempt, solution, guess);
    // } else if (attempt == attempts) {
    //     checkAttempts(attempt, solution, guess); // std::cout << "You didn't find the word" << std::endl;
    // }


    std::cout << attempts +2 << std::endl;

}