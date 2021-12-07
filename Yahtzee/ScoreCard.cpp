#include "ScoreCard.h"
#include <fstream>
#include <ostream>


const int ScoreCard::MAX_SCORES = 7;

// Display the scorecard, game number and the date for an ALREADY existing game history 
void ScoreCard::displayScoreCard(int gameNumber, const int MAX_GAMES) const {
    assert(gameNumber <= MAX_GAMES);

    // Display the Game Number 
    cout << "Game: " << gameNumber << " of " << MAX_GAMES << endl;

    // Display the Date 
    cout << "Date: " << timebuf << endl;

    // Display the ScoreCard 
    cout << endl;
    cout << "----- SCORECARD -----" << endl;
    cout << "Aces:     " << scores[0] << endl;
    cout << "Twos:     " << scores[1] << endl;
    cout << "Threes:   " << scores[2] << endl;
    cout << "Fours:    " << scores[3] << endl;
    cout << "Fives:    " << scores[4] << endl;
    cout << "Sixes:    " << scores[5] << endl;

    // Print the total 
    displayTotal();
    cout << endl;
}

// Display just the scorecard for a game that is being CREATED 
void ScoreCard::displayScoreCard() const {
    string values[6] = { "Aces", "Twos", "Threes", "Fours", "Fives", "Sixes" };

    cout << endl;
    cout << "----- SCORECARD -----" << endl;
    for (int i = 0; i < MAX_SCORES - 1; i++) {

        // Print the Value out
        cout << values[i] << ": ";

        // If the score is not equal to -1, then do not print the value out as it has not been set
        if (scores[i] != -1) {
            cout << scores[i];
        }

        cout << endl;
    }

    // Print the total 
    displayTotal();

    cout << endl;
}

// Read the time stamp scorecard
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
