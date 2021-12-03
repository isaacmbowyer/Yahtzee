#include "ScoreCard.h"
#include <fstream>
#include <ostream>


const int ScoreCard::MAX_SCORES = 7; 

void ScoreCard::displayScoreCard(int gameNumber, const int MAX_GAMES) const {
    // Display the Game Number 
    cout << "Game: " << gameNumber << " of " << MAX_GAMES << endl;

    // Display the Date 
    cout << "Date: " << timebuf << endl; 

    // Display the ScoreCard 
    cout << endl;
    cout << "----- SCORECARD -----" << endl;
    cout << "Aces: " << scores[0] << endl;
    cout << "Twos: " << scores[1] << endl;
    cout << "Threes: " << scores[2] << endl;
    cout << "Fours: " << scores[3] << endl;
    cout << "Fives: " << scores[4] << endl;
    cout << "Sixes: " << scores[5] << endl;
    
    // Print the total 
    displayTotal(); 
    cout << endl;
}

void ScoreCard::displayScoreCard() const {
    string values[6] = { "Aces", "Twos", "Threes", "Fours", "Fives", "Sixes" };
    
    cout << endl;
    cout << "----- SCORECARD -----" << endl;
    for (int i = 0; i < MAX_SCORES - 1; i++) {
        
        // Print the Value out
        cout << values[i] << ": "; 

        // If the score is equal to NULL, then do not print the value out as it has not been set
        if (scores[i] != NULL) {
            cout << scores[i];
        }

        cout << endl;
    }

    // Print the total 
    displayTotal();
  
    cout << endl;
}

istream& operator>>(istream& is, ScoreCard& scoreCard) {
    // Get the scores
    char deliminator; 
    for (int i = 0; i < scoreCard.MAX_SCORES; i++) {
        is >> scoreCard.scores[i];
        is.get(deliminator);
    }

    // Get the Time stamp 
    string timeStamp;
    getline(is, timeStamp, '\n');
    strcpy_s(scoreCard.timebuf, timeStamp.length() + 1, timeStamp.c_str());

    return is;
}