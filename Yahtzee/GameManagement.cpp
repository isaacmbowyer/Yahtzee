#include "GameManagement.h"
#include "ScoreCard.h" 
#include <time.h>
#include <iostream>
using namespace std;

const int GameManagement::MAX_DICES = 5;
const int GameManagement::MAX_TURNS = 6;
const int GameManagement::MAX_ROLLS = 3;

GameManagement::GameManagement() {
    // Stores the dice rolled values 
    diceValues = (int*) calloc(MAX_DICES, sizeof(int));

    // Stores if we have locked the dice as a boolean value 
    lockedDices = (bool*) malloc(sizeof(bool) * MAX_DICES); 

    // Create a Scorecard 
    scoreCard = new ScoreCard(); 
    scoreCard->setDefaultValues();
}
GameManagement::~GameManagement() {
    free(diceValues);
    free(lockedDices);
}

void GameManagement::start(){
    srand(time(nullptr));
    for (int turn = 1; turn <= MAX_TURNS; turn++) {
        cout << "Turn #" << turn << " of " << MAX_TURNS << endl;
        cout << "------------" << endl << endl;

        setDefaultValues(); // set all dice locked positions to be false

        for (int roll = 1; roll <= MAX_ROLLS; roll++) {
            cout << "Dice Roll Set #" << roll << " of " << MAX_ROLLS << endl;
            cout << "---------------------" << endl;

            scoreCard->displayScoreCard();

            // Roll the Dice
            rollDice(); 

            // Display Each Dice
            cout << " Dice 1 \t" << " Dice 2 \t" << " Dice 3 \t" << " Dice 4 \t" << " Dice 5 \t" << endl;
            for (int line = 1; line <= 7; line++) {
                displayDiceFaces(line);
            }
            cout << endl; 

            toggleDice(); 
            
        }

        displayOptions(); 
        getScoreOption(); 


    }
}

// I struggled with this. I spent days trying to solve it and sadly I just gave up in the end -> This is the best I could do. 
void GameManagement::displayDiceFaces(const int line) {
    for (int diceNumber = 1; diceNumber <= MAX_DICES; diceNumber++) {
        // If the dice has been locked, then we change the symbol
        char symbol = '*';
        if (lockedDices[diceNumber - 1]) {
            symbol = '#';
        }
        int dice = diceValues[diceNumber - 1];
        // Dectect which line we are on 
        switch(line){
        case 1:
                cout << symbol << symbol << symbol << symbol << symbol << symbol << symbol << symbol << symbol << "\t";
                break;
            case 2: 
                cout << symbol << " ";
                switch (dice) {
                    case 1:
                        cout << "    1 ";
                        break;
                    case 2:
                        cout << "22222 ";
                        break;
                    case 3:
                        cout << "33333 ";
                        break;
                    case 4:
                        cout << "4   4 ";
                        break;
                    case 5:
                        cout << "55555 ";
                        break;
                    default:
                        cout << "66666 ";
                        break;
                }
                cout << symbol << "\t";
                break; 
            case 3: 
                cout << symbol << " ";
                switch (dice) {
                    case 1:
                        cout << "    1 ";
                        break;
                    case 2:
                        cout << "    2 ";
                        break;
                    case 3:
                        cout << "    3 ";
                        break;
                    case 4:
                        cout << "4   4 ";
                        break;
                    case 5:
                        cout << "5     ";
                        break;
                    default:
                        cout << "6     ";
                        break;
                }
                cout << symbol << "\t";
                break;
            case 4:
                cout << symbol << " ";
                switch (dice) {
                    case 1:
                        cout << "    1 ";
                        break;
                    case 2:
                        cout << "22222 ";
                        break;
                    case 3:
                        cout << "  333 ";
                        break;
                    case 4:
                        cout << "44444 ";
                        break;
                    case 5:
                        cout << "55555 ";
                        break;
                    default:
                        cout << "66666 ";
                        break;
                }
                cout << symbol << "\t";
                break;
            case 5:
                cout << symbol << " ";
                switch (dice) {
                    case 1:
                        cout << "    1 ";
                        break;
                    case 2:
                        cout << "    2 ";
                        break;
                    case 3:
                        cout << "    3 ";
                        break;
                    case 4:
                        cout << "    4 ";
                        break;
                    case 5:
                        cout << "    5 ";
                        break;
                    default:
                        cout << "6   6 ";
                        break;
                }
                cout << symbol << "\t";
                break;
            case 6:
                cout << symbol << " ";
                switch (dice) {
                    case 1:
                        cout << "    1 ";
                        break;
                    case 2:
                        cout << "22222 ";
                        break;
                    case 3:
                        cout << "33333 ";
                        break;
                    case 4:
                        cout << "    4 ";
                        break;
                    case 5:
                        cout << "55555 ";
                        break;
                    default:
                        cout << "66666 ";
                        break;
                }
                cout << symbol << "\t";
                break;
            default:
                cout << symbol << symbol << symbol << symbol << symbol << symbol << symbol << symbol << symbol << "\t";
                break;
        }
    }
    cout << endl;
}

void GameManagement::rollDice() {
    for (int i = 0; i < MAX_DICES; i++) {
        // Dont roll the dice if its locked
        if (!lockedDices[i]) {
            diceValues[i] = rand() % 6 + 1;
        }
    }
}

// Display the options to score against 
void GameManagement::displayOptions() const {
    string scores[6] = { "Aces", "Twos", "Threes", "Fours", "Fives", "Sixes" }; 
    for (int i = 1; i < scoreCard->getMaxScores(); i++) {
        // Check if the the score has not already been scored on the scorecard
        if (scoreCard->checkIfScored(i - 1)) {
            cout << i << ":\t" << scores[i - 1] << endl;
        }
    }

}

void GameManagement::toggleDice() {
    int userInput;
    do {
        cout << "Enter a dice number to toggle held state. Enter any other number to roll again: ";
        // Get input from user 
        cin >> userInput;

        switch (userInput) {
            case 1:
                lockedDices[0] = true;
                break;
            case 2:
                lockedDices[1] = true;
                break;
            case 3:
                lockedDices[2] = true;
                break;
            case 4:
                lockedDices[3] = true;
                break;
            case 5:
                lockedDices[4] = true;
                break;
            case 6:
                lockedDices[5] = true;
                break;
        }

    } while (userInput >= 1 && userInput <= MAX_DICES);
    cout << endl;
}

// Get the User Input to see which dice to score against and checks to see that it is valid 
const int GameManagement::getScoreOption(){
    bool validInput = true; // assume true 
    int userInput;
    do {
        // Get input from user 
        cout << "Score against: ";
        cin >> userInput;
          
        if (!userInput >= 1 && userInput <= MAX_ROLLS) {
            // User entered invalid number
            validInput = false; 
        }

        else if (scoreCard->checkIfScored(userInput - 1)) {
            // User already entered a value that is already scored
            cout << "You already scored this"  << endl; 
        }

    } while (!validInput);

    return userInput; 
}