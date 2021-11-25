#include "ScoreCard.h"
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

const int ScoreCard::MAX_SCORES = 6; 

// Display the score card to the user 
void ScoreCard::displayScoreCard() {

}

// Retrieve and set all the score cards from the file 
istream& operator>>(istream& is, ScoreCard& scoreCard) {
    char deliminator;

    // Retrieve all the scores from the file 
    for (int i = 0; i < ScoreCard::MAX_SCORES; i++) { // use for loop to reduce repeating code 
        is >> scoreCard.scores[i]; // get the file and put it into the array
        is.get(deliminator);  // get the deliminator 
    }

    // Calculate the total 
    

    // Retrieve the time_stamp 


    return is; 
}
