#include <cassert>

#include "wordle.H"

int main() {
    // test checkGuess and isAllMatch
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
    
    // just choose a solution that is 5 letters
    std::string solution = "match";
    std::cout << "Testing checkGuess function" << std::endl;
    std::string guess = "earth";
    checkGuess(matches, attempt, solution, guess);

    

    assert(guess.length() == 5);
    assert(matches[0][4] == 2);
    assert(matches[0][1] && matches[0][3] == 1);
    assert(matches[0][0] && matches[0][2] == 0);
    assert(isAllMatch(solution, guess) == 0);

    std::cout << "Tests passed";
}