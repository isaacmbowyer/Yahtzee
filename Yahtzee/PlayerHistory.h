#pragma once
#include "Player.h"
#include "ScoreCard.h"
class PlayerHistory
{
public:
    PlayerHistory(Player* player, const string& PLAYER_FILE); 
    ~PlayerHistory();
    void start(); 
    void gameHistoryMain();
    void getPlayerStats(); 
    void displayMenu() const;
    void displayGameHistoryMenu(int ptr) const;
    void displayPlayerHistory() const;
    void getScoreCards(); 
    void setNewGameHistory(const int newScore);
    void reallocScoreCards(ScoreCard* newScoreCard);
    void freeMemory();

    void writePlayerHistory();
    friend istream& operator>>(istream& is, PlayerHistory& history);
    friend ostream& operator<<(ostream& os, PlayerHistory& player);

private:
    Player* player; 
    double* gameHistory; 
    ScoreCard** scoreCards; 
    const string PLAYER_FILE;
    static const int MAX_HISTORIC_DATA;
};

// I was going to do this via operator overload based on the game management class however, i figured that the game management class should not control the player history -> only the game 
inline void PlayerHistory::setNewGameHistory(const int newScore) {
    // Increment total score
    gameHistory[0]++;

    // Increment accumulated score
    gameHistory[1] += newScore; 

    // Set the new average Score
    gameHistory[2] = (gameHistory[1] / gameHistory[0]);

}

// Free player history data 
inline void PlayerHistory::freeMemory() {
    delete this;
}

// Write the game history to the file
inline ostream& operator<<(ostream& os, PlayerHistory& playerHistory) {
    os << playerHistory.gameHistory[0] << ','; 
    os << playerHistory.gameHistory[1] << ','; 
    os << playerHistory.gameHistory[2] << endl;

    return os;
}