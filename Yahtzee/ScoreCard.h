#pragma once 
#include <iostream>
#include <string>
using namespace std;
class ScoreCard
{
public:
    inline ScoreCard();
    void displayScoreCard(int gameNumber, const int MAX_GAMES) const;
    void displayScoreCard() const; 
    void displayTotal() const; 
    void setDefaultValues(); 
    const int getMaxScores() const; 
    const bool checkIfScored(const int value) const; 
    friend istream& operator>>(istream& is, ScoreCard& scoreCard);
private:
    char timebuf[30];
    int* scores;
    static const int MAX_SCORES; 
};


inline ScoreCard::ScoreCard() {
    scores = (int*) malloc(sizeof(int) * MAX_SCORES); // stores all the scores of the scorecard in a heap array 
}

// Display the total for the scorecard
inline void ScoreCard::displayTotal() const {
    cout << "---------------------" << endl;
    cout << "Total:" << scores[6] << endl;
    cout << "---------------------" << endl;
}

// Sets default values when we create a scorecard
inline void ScoreCard::setDefaultValues() {
    for (int i = 0; i < MAX_SCORES - 1; i++) {
        scores[i] = NULL;
    }
    // Set the Total to be 0   
    scores[MAX_SCORES - 1] = 0;
}
// Returns the max scores 
inline const int ScoreCard::getMaxScores() const {
    return MAX_SCORES; 
}

// Checks to see if the value has already been used up 
inline const bool ScoreCard::checkIfScored(const int value) const {
    return scores[value] == NULL; 
}