#pragma once
#include <iostream>
using namespace std;

class ScoreCard
{
public:
    inline ScoreCard(); 
    void displayScoreCard() const;
    friend istream& operator>>(istream& is, ScoreCard& scoreCard);
private:
    int* scores;
    static const int MAX_SCORES;
};


inline ScoreCard::ScoreCard() {
    scores = (int*) calloc(MAX_SCORES, sizeof(int)); // stores all the scores of the scorecard in a heap array, defaulted to 0 
}
