#include <iostream>
#include <string>
#include <vector>

#include "wordle.H"

int main() {

int attempt = 0;

    chooseSolution(5);
    startGame();
    while (guess != solution) {
        if (attempt <= attempts) {
            checkGuess();
            attempt += 1;
        }
    }
}

// could maybe use the diff check to see if the words match?