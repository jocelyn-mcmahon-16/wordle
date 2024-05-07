#include <cassert>

#include "wordle.H"

int main() {
    // test checkGuess and isAllMatch
    const int word_length = 5;
    const int NOT_MATCH = 0;
    const int PARTIAL_MATCH = 1;
    const int MATCH = 2;
    int attempts = 6;

    std::string guess;
    int attempt = 0;

    std::vector<std::vector<int>> matches(attempts, std::vector<int>(word_length));
    
    // just choose a solution that is 5 letters for comparison purposes
    std::string solution = "match";
    std::cout << "Testing checkGuess and isAllMatch functions." << std::endl;
    guess = "earth";
    checkGuess(matches, attempt, solution, guess);

    assert(guess.length() == 5);
    assert(matches[0][4] == 2);
    assert(matches[0][1] && matches[0][3] == 1);
    assert(matches[0][0] && matches[0][2] == 0);
    assert(isAllMatch(solution, guess) == 0);

    std::cout << "Tests passed!";
}