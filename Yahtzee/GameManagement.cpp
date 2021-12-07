#include "GameManagement.h"
#include <time.h>
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

const int GameManagement::MAX_DICES = 5;
const int GameManagement::MAX_TURNS = 6;
const int GameManagement::MAX_ROLLS = 3;

GameManagement::GameManagement() {
    // Stores the dice rol values 
    dices = new vector<Dice*>;
    
    // Create the dices and add them into the vector
    for (int i = 0; i < MAX_DICES; i++) {
        dices->push_back(new Dice());
    }

    // Create a Scorecard 
    scoreCard = new ScoreCard(); 
    scoreCard->setDefaultValues(); 
}
GameManagement::~GameManagement() {
    // Free each dice 
    for (int i = 0; i < MAX_DICES; i++) {
        delete dices->at(i);
    }

    // Free the dice array
    delete dices; 
    dices = nullptr; 
}
// Start the application 
ScoreCard& GameManagement::start(){
    srand(time(nullptr));

    // Set the time for the scorecard
    scoreCard->setTime(); 

    // For each turn/round ...
    for (int turn = 1; turn <= MAX_TURNS; turn++) {
        // Display the turn number
        cout << "Turn #" << turn << " of " << MAX_TURNS << endl;
        cout << "------------" << endl;

        // For each roll ...
        for (int roll = 1; roll <= MAX_ROLLS; roll++) {
            // Display the dice number
            cout << endl; 
            cout << "Dice Roll Set #" << roll << " of " << MAX_ROLLS << endl;
            cout << "---------------------" << endl;

            scoreCard->displayScoreCard();

            // Roll the Dices
            rollAllDice(); 

            // Display Each Dice
            cout << " Dice 1 \t" << " Dice 2 \t" << " Dice 3 \t" << " Dice 4 \t" << " Dice 5 \t" << endl;
            for (int line = 1; line <= 7; line++) {
                displayDiceFaces(line);
            }
            cout << endl; 

            // Check that the roll is not the last, you cannot toggle a dice on the last roll
            if (roll != MAX_ROLLS) {
                // Get Input to toggle the dice 
                getInputToToggleDice();
            }

        }
        // Round/Turn is over, display the options the user can have to score
        displayOptions(); 

        // Get the User to input a score option
        const int score = getScoreOption(); 
        
        // Get how many times that the score is equal to what the user wants 
        vector<Dice*>::iterator::difference_type result;
        result = count_if(dices->begin(), dices->end(), [score](Dice* dice) {
            return (*dice == score); 
        });
        
        // Times the result by the score 
        result *= score; 
        
        // Set the required scorecard's score 
        scoreCard->setScore(score - 1, result);

        // Set the new total 
        *scoreCard += result;

        // Unlock the dice 
        resetAllDice(); 

        cout << endl; 
    }

    // Return the scorecard
    return *scoreCard; 
}

// Display the dice faces to the user
void GameManagement::displayDiceFaces(const int line) {
    assert(line >= 1 && line <= 7);

    for_each(dices->begin(), dices->end(), [line](Dice* dice) {
        // If the dice has been locked, then we change the symbol
        char symbol = '*';
        if (dice->checkIfLocked()) {
            symbol = '#';
        }

        // Get the dice number
        int diceValue = dice->getDiceValue();

        // Detect which line we are one and the dice number and print its required section 
        switch (line) {
        case 1:
            cout << symbol << symbol << symbol << symbol << symbol << symbol << symbol << symbol << symbol << "\t";
            break;
        case 2:
            cout << symbol << " ";
            switch (diceValue) {
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
            switch (diceValue) {
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
            switch (diceValue) {
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
            switch (diceValue) {
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
            switch (diceValue) {
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

    });
    // New line    
    cout << endl;
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

void GameManagement::getInputToToggleDice() {
    // Check if all the dices have been toggled -> the user will not be able to get the option to toggle a dice
    if (!all_of(dices->begin(), dices->end(), [](Dice* dice) { return dice->checkIfLocked(); })) {
        int input; 
        do {
            cout << "Enter dice number to toggle held state. Enter any other number to roll again: ";
            cin >> input;

            if (input > 0 && input <= MAX_DICES) {
                // User entered a correct range but we need to check if the dice is already toggled 
                Dice* dice = dices->at(input - 1);

                if (dice->checkIfLocked()) {
                    cout << "This dice is already locked. Please enter another dice" << endl;
                }
                else {
                    // Lock the dice 
                    dice->toggleDice(true);
                }
            }

        } while (input > 0 && input <= MAX_DICES); 
    }

    // All dice toggled, dont ask for input 
    else {
        cout << "Cannot lock any more dice as they have all been toggled" << endl; 
    }
 
}

// Get the User Input to see which dice to score against and checks to see that it is valid 
const int GameManagement::getScoreOption(){
    bool validInput = true; // assume true 
    int userInput;
    do {
        // Get input from user 
        cout << "Score against: ";
        cin >> userInput;
          
        // Check if the userinput is in the valid parameters 
        if (userInput <= 0 || userInput > scoreCard->getMaxScores()) {
            // User entered invalid number
            cout << "Invalid Input. Please enter a number from 1 to 6" << endl; 
            validInput = false; 
        }
        else if (!scoreCard->checkIfScored(userInput - 1)) {
            // User already entered a value that is already scored
            cout << "You already scored this"  << endl; 
            validInput = false; 
        }
        else {
            validInput = true;
        }

    } while (!validInput);

    return userInput; 
}