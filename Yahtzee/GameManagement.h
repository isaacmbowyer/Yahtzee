#pragma once
#include "ScoreCard.h"
class GameManagement
{
public:
    GameManagement(); 
    ~GameManagement();
    void start(); 
    void displayDiceFaces(const int line);
    void displayOptions() const; 
    void setDefaultValues(); 
    void rollDice();
    const int getScoreOption();
    void toggleDice();
private:
    ScoreCard* scoreCard;
    int* diceValues; 
    bool* lockedDices;
    static const int MAX_DICES; 
    static const int MAX_TURNS; 
    static const int MAX_ROLLS; 
};

// Sets every locked dice to be false  at the start
inline void GameManagement::setDefaultValues() {
    for (int i = 0; i < MAX_DICES; i++) {
        lockedDices[i] = false; 
    }
}
