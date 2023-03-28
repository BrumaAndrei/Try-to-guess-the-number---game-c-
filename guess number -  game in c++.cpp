#include <iostream>
#include <cmath>
#include <cctype>
#include <stdlib.h>
#include <ctime>
using namespace std;

void PlayGame();
bool WantToPlayAgain();
bool IsGameOver(int secretNumber, int numberOfTries, int guess);
int GetGuess(int numberOfTries);
void DisplayResult(int secretNumber, int numberOfTries);

const int IGNORE_CHARS = 256;

int main() {
    srand((unsigned int)time(NULL));
    do {
        PlayGame();
    } while (WantToPlayAgain());


    return 0;
}

void PlayGame() {
    int UPPER_BOUND = rand() % 900 + 100;
    int secretNumber = rand() % UPPER_BOUND + 1;
    int numberOfTries = (int)ceil(log2(UPPER_BOUND));
    int guess = 0;

    cout << "The range of numbers is between 0 and " << UPPER_BOUND << "\n";
    do {
        guess = GetGuess(numberOfTries);
        if (guess != secretNumber) {
            --numberOfTries;
            if (guess > secretNumber) {
                cout << "Your guess was too high!\n";
            }
            else {
                cout << "Your guess was too low!\n";
            }
        }

    } while (!IsGameOver(secretNumber, numberOfTries, guess));

    DisplayResult(secretNumber, numberOfTries);
}

bool WantToPlayAgain() {
    char input;
    bool failure;

    do {
        failure = false;
        cout << "Would you like to play again? (y/n)\n";
        cin >> input;
        if (!isalpha(input)) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            cout << "Input error! Please try again!\n";
            failure = true;
        }
        else {
            cin.ignore(IGNORE_CHARS, '\n');
            input = tolower(input);
        }

    } while (failure);
    return input == 'y';
}

bool IsGameOver(int secretNumber, int numberOfTries, int guess) {
    return secretNumber == guess || numberOfTries <= 0;
}

int GetGuess(int numberOfTries) {
    int guess;
    bool failure;

    do {
        failure = false;
        cout << "Please enter your guess (number of guesses left is " << numberOfTries << ")\n";
        cin >> guess;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(IGNORE_CHARS, '\n');
            cout << "Input error1 Please try again!\n";
            failure = true;
        }
    } while (failure);
    return guess;
}

void DisplayResult(int secretNumber, int numberOfTries) {
    if (numberOfTries > 0) {
        cout << "You got it! It was " << secretNumber << "\n";
    }
    else {
        cout << "You did't get it... It was " << secretNumber << "\n";
    }
}
