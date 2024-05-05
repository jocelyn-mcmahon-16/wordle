#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "wordle.H"

int main() {
    
    const int word_length = 5;
    const int NOT_MATCH = 0;
    const int PARTIAL_MATCH = 1;
    const int MATCH = 2;
    const int num_guesses = 6;
    int attempts = 6;

    std::string guess;
    int attempt = 0;

    std::vector<std::string> tries(attempts);    
    std::vector<std::vector<int>> matches(attempts, std::vector<int>(word_length));

    std::string solution = chooseSolution();
    raiseCase(solution);


    startGame(tries, matches, attempt);
    std::cout << "Enter your guess (word length must be " + std::to_string(word_length) + ") or type Q to quit: ";


    while (attempt < attempts) {
      
        do {
            std::getline(std::cin, guess);
            raiseCase(guess);
        } while (guess != "Q" && !isValid(guess));
        
        if (guess == "Q") {
            std::cout << "Quit game" << std::endl;
            break;
        }
        tries[attempt] = guess;
        checkGuess(matches, attempt, solution, guess);
        printGuesses(tries, matches, attempt);
        attempt++;
        if (isAllMatch(solution, guess)) {
            std::cout << "You found the word! :D" << std::endl;
            checkAttempts(attempt, solution, guess);
            break;
        } else if (attempt == attempts) {
            std::cout << "You didn't find the word... :'(" << std::endl;
            checkAttempts(attempt, solution, guess);
        }
    }
}