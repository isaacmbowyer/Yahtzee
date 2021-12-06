#pragma once
#include <iostream>
using namespace std;
class Dice
{
public:
    Dice(); 
    void roll(); 
    const int getDiceValue() const;
    void toggleDice(bool value);
    const bool checkIfLocked() const; 

    bool operator==(const int score) const;
private:
    int diceValue; 
    bool locked;
};

inline Dice::Dice() { 
    // Lock is defaulted to be false once created 
    locked = false;

    // Dice not rolled yet set to 0
    diceValue = 0; 
}

// Roll the dice only if the dice is not locked 
inline void Dice::roll() {
    if (!locked) {
        diceValue = rand() % 6 + 1;
    }
}

// Return the dice value so it can be displayed 
inline const int Dice::getDiceValue() const {
    return diceValue;
}

// Lock or unlock the dice 
inline void Dice::toggleDice(bool value) {
    locked = value; 
}

// Check if the dice has been locked
inline const bool Dice::checkIfLocked() const {
    return locked; 
}

// Check if the dice value is equal to the score 
inline bool Dice::operator==(const int score) const {
    return diceValue == score; 
}