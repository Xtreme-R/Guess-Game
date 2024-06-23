#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Function prototypes
int getRandomNumber(int max);
void playGame(int max, vector<int>& scores);
void showLeaderboard(const vector<int>& scores);
void clearInputStream();

int main() {
    // Seed the random number generator
    srand(time(0));
    vector<int> scores;
    char choice;

    do {
        int maxNumber;
        cout << "Welcome to the Enhanced Guessing Game!" << endl;
        cout << "Select difficulty level:" << endl;
        cout << "1. Easy (1-50)" << endl;
        cout << "2. Medium (1-100)" << endl;
        cout << "3. Hard (1-200)" << endl;
        cout << "Enter your choice: ";
        int level;
        cin >> level;

        // Set the maximum number based on difficulty level
        switch(level) {
            case 1: maxNumber = 50; break;
            case 2: maxNumber = 100; break;
            case 3: maxNumber = 200; break;
            default: maxNumber = 100; break;
        }

        playGame(maxNumber, scores);

        cout << "Do you want to play again? (Y/N): ";
        cin >> choice;
        choice = toupper(choice);

    } while(choice == 'Y');

    showLeaderboard(scores);

    return 0;
}

int getRandomNumber(int max) {
    return rand() % max + 1;
}

void playGame(int max, vector<int>& scores) {
    int randomNumber = getRandomNumber(max);
    int guess;
    int attempts = 0;
    bool hintUsed = false;

    cout << "I have generated a random number between 1 and " << max << "." << endl;
    cout << "Can you guess what it is?" << endl;

    do {
        cout << "Enter your guess: ";
        while (!(cin >> guess)) {
            clearInputStream();
            cout << "Invalid input. Please enter a numeric value: ";
        }
        attempts++;

        if (guess > randomNumber) {
            cout << "Too high! Try again." << endl;
        } else if (guess < randomNumber) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts." << endl;
            scores.push_back(attempts);
        }

        if (!hintUsed && abs(guess - randomNumber) <= 10 && guess != randomNumber) {
            cout << "Hint: You're within 10 numbers of the correct answer!" << endl;
            hintUsed = true;
        }

    } while (guess != randomNumber);
}

void showLeaderboard(const vector<int>& scores) {
    cout << "\nLeaderboard:" << endl;
    if (scores.empty()) {
        cout << "No games played yet." << endl;
        return;
    }

    vector<int> sortedScores = scores;
    sort(sortedScores.begin(), sortedScores.end());

    for (size_t i = 0; i < sortedScores.size(); ++i) {
        cout << i + 1 << ". " << sortedScores[i] << " attempts" << endl;
    }
}

void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
