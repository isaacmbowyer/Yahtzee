#pragma once
#include "Dice.h"
#include "ScoreCard.h"
#include <algorithm>
#include <vector>"
class GameManagement
{
public:
    GameManagement(); 
    ~GameManagement();
    ScoreCard& start();
    void displayDiceFaces(const int line);
    void displayOptions() const; 
    const int getScoreOption();
    void rollAllDice();
    void getInputToToggleDice();
    void resetAllDice(); 

    void freeMemory();
private:
    ScoreCard* scoreCard;
    vector<Dice*>* dices;
    static const int MAX_DICES; 
    static const int MAX_TURNS; 
    static const int MAX_ROLLS; 
};

// Roll all dices using for_each 
inline void GameManagement::rollAllDice() {
    for_each(dices->begin(), dices->end(), [](Dice* dice) {
        // Get the actual dice to roll itself
        dice->roll(); 
    });
}

// Unlock each dice using for_each
inline void GameManagement::resetAllDice() {
    for_each(dices->begin(), dices->end(), [](Dice* dice) {
        // Get the actual dice to unlock itself 
        dice->toggleDice(false);
    });
}

// Free memory 
inline void GameManagement::freeMemory() {
    delete this;
}