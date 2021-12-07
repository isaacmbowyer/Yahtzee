#pragma once
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
class ScoreCard
{

public:
    ScoreCard();
    ~ScoreCard();
    void displayScoreCard(int gameNumber, const int MAX_GAMES) const;
    void displayScoreCard() const;
    void displayTotal() const;

    const bool checkIfScored(const int value) const;

    void setDefaultValues();
    void setScore(const int index, const int value);
    void setTime();

    const int getMaxScores() const;
    const int getTotal() const;

    ScoreCard& operator+=(const int value);
    friend istream& operator>>(istream& is, ScoreCard& scoreCard);
    friend ostream& operator<<(ostream& os, ScoreCard& scoreCard);

private:
    char timebuf[30];
    int* scores;
    static const int MAX_SCORES;
};

inline ScoreCard::ScoreCard() {
    // stores all the scores of the scorecard in a heap array 
    scores = (int*) malloc(sizeof(int) * MAX_SCORES);
}

// Freee the scores array
inline ScoreCard::~ScoreCard() {
    delete[] scores;
    scores = nullptr; 
}


// Display the total for the scorecard
inline void ScoreCard::displayTotal() const {
    cout << "---------------------" << endl;
    cout << "Total:    " << scores[6] << endl;
    cout << "---------------------" << endl;
}

// Checks to see if the value has already been used up 
inline const bool ScoreCard::checkIfScored(const int value) const {
    return scores[value] == -1;
}


// Returns the max scores 
inline const int ScoreCard::getMaxScores() const {
    return MAX_SCORES;
}

// Return the total score
inline const int ScoreCard::getTotal() const {
    return scores[6];
}

// Sets default values when we create a scorecard
inline void ScoreCard::setDefaultValues() {
    for (int i = 0; i < MAX_SCORES - 1; i++) {
        scores[i] = -1;
    }

    // Set the Total to be 0   
    scores[6] = 0;
}

// Set the value for the required score card
inline void ScoreCard::setScore(const int index, const int value) {
    assert(index < MAX_SCORES);

    scores[index] = value;
}

// Set the time for the scorecard
inline void ScoreCard::setTime() {
    time_t now = time(nullptr);
    ctime_s(timebuf, sizeof(timebuf), &now);
}

// Adds Scorecard total 
inline ScoreCard& ScoreCard::operator+=(const int value) {
    scores[6] += value;
    return *this;
}

// Write the scorecard contents to the file
inline ostream& operator<<(ostream& os, ScoreCard& scoreCard) {
    // Write each score 
    os << scoreCard.scores[0] << ',' << scoreCard.scores[1] << ',' << scoreCard.scores[2] << ',' << scoreCard.scores[3] << ',';
    os << scoreCard.scores[4] << ',' << scoreCard.scores[5] << ',' << scoreCard.scores[6] << ',';

    // Write the time 
    os << scoreCard.timebuf << endl;

    return os;
}