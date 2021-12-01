#pragma once
#include "Player.h"
#include "ScoreCard.h"
class PlayerHistory
{
public:
    PlayerHistory(Player* player); 
    ~PlayerHistory();
    void start(); 
    void gameHistoryMain();
    void getPlayerStats(); 
    void displayMenu() const;
    void displayGameHistoryMenu(int ptr) const;
    void displayPlayerHistory() const;

    void getScoreCards(); 
    friend istream& operator>>(istream& is, PlayerHistory& history);
private:
    Player* player; 
    double* gameHistory; 
    ScoreCard** scoreCards; 
    const string PLAYER_FILE = "Hulk.csv";
    static const int MAX_HISTORIC_DATA;
    static int HELLO; 
};

