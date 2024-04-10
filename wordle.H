// need the dictionary of all the possible words
// then need to randomly pick one
    // n = rand() % 2309; // as far as I'm aware, there are 2309 wordle words, I'll use that list
// then need to have functions for guesses
    // need an input for all 5 letters, then separate them internally to check if each one is correct
    // re-output the same word with some symbol or color that would indicate if it is correct
    // x for not in the word, o for in the word put wrong place, * or ^ for correct?
    // or could do colors if I can figure that out, would be cool
        // would want to make a dictionary? color has a value that can be more easily compared?
// They should only be able to guess 6 times, like the real game
    // so I'd need a loop that only runs 6 times, or until they guess the correct word



#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <random>
#include <vector>
#include <iterator>

// basic needs: a solution, a guess.

const int word_length = 5;
const int attempts = 6;
int attempt = 0;

std::string word;
std::string solution;
std::string guess;


// class word {
//     private:
    

//     public:

// }

// we want color!
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"

enum class Color { red = 31, green = 32, yellow =33 };
Color c = Color::red;
switch(c) {
    case Color::red : std::cout << "red\n"; break;
    case Color::green : std::cout << "green\n"; break;
    case Color::yellow : std::cout << "blue\n"; break;
};


// input

// get guess
// has to be 5 letters, if it isn't, ask for a 5 letter guess
// or just have them input each thing individually? but then they can't erase while writing if they want to change the guess...

// check guess

// 


std::vector<std::string> SolutionList(int word_length) {
    std::string line;
    std::vector<std::string> word_list;

    std::ifstream fin;
    fin.open("./words.txt");
    while (getline(fin, line)) {
        if (line.length() == word_length) {
            word_list.push_back(line);
        }
    }
    fin.close();
    return word_list;
};

// the folowing block of code I *think* renders the above one obsolete
// the input for this should just be starting the game, so maybe swap words as the input for length?
std::string chooseSolution(std::vector<std::string> words) {
    // pick a random word from the list of words
    std::vector<std::string> words;
    std::ifstream file ("words.txt");
    std::string line;
    while (getline(file, line)) {
        if (line.length() == word_length){
            words.push_back(line);
        }
    }
    std::string solution = words[rand() % words.size()];
    return solution;
};


std::string startGame(int word_length) {
    std::cout << "Welcome to Wordle!" << std::endl;
    std::cout << "You have 6 attempts to guess a 5 letter word." << std::endl;
    std::cout << "Letters that are not in the word will be printed in red, \n letters in the word but not in the correct position will be printed in yellow, \n and letters that are in the correct position will be printed in green." << std::endl;
    std::cin >> guess;
};


std::string checkGuess(std::string guess){
    // change colors
    // attempt += 1;
    // std::cin >> new_guess;
};

// return if the thing is true or not?


int getAttempts() {

};