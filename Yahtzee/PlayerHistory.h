#pragma once
#include "Player.h"
class PlayerHistory
{
public:
    PlayerHistory(string& playerFile); 
    ~PlayerHistory();
    void start(); 
    void getPlayerHistoryData(); 
    void displayMenu() const;
    void displayPlayerHistory() const;
    friend istream& operator>>(istream& is, PlayerHistory& history);
private:
    Player* player; 
    int** scoreCards;  // stores the scorecards for the player in a 2D array
    int*  historyData; // stores the historic history data from player
    const string PLAYER_FILE;
    static const int MAX_HISTORIC_DATA;
};

