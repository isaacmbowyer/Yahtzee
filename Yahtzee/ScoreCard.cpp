#include "ScoreCard.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

const int ScoreCard::MAX_SCORES = 7; 

// Display the score card to the user 
void ScoreCard::displayScoreCard() const {
    cout << endl;
    cout << "----- SCORECARD -----" << endl; 
    cout << "Aces: " << scores[0] << endl; 
    cout << "Twos: " << scores[1] << endl;
    cout << "Threes: " << scores[2] << endl;
    cout << "Fours: " << scores[3] << endl;
    cout << "Fives: " << scores[4] << endl;
    cout << "Sixes: " << scores[5] << endl;
    cout << "---------------------" << endl;
    cout << "Total:" << scores[6] << endl; 
    cout << "---------------------" << endl;
    cout << endl;
}

istream& operator>>(istream& is, ScoreCard& scoreCard) {
    char deliminator;
    // Loop through the Score Array and set each score value 
    for (int i = 0; i < ScoreCard::MAX_SCORES; i++) {
        is >> scoreCard.scores[i]; // set and retrieve value 
        is.get(deliminator); // get the deliminator 
    }
  
    return is;
}


