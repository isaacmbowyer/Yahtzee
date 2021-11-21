#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "Player.h"
using namespace std;
class PlayerManagement
{
public:
    PlayerManagement();
    ~PlayerManagement();
    void start(); 
    void displayMenu();
    void getExistingPlayers();
    void writeExistingPlayers();
    void displayExistingPlayers();

    const vector<string> choosePlayer() const;
    void addPlayer();
    void removePlayer();

    friend inline bool sortByHighScore(const Player* lhs, const Player* rhs);
    friend inline bool sortByUsername(const Player* lhs, const Player* rhs);


    friend istream& operator>>(istream& is, PlayerManagement& management);


private:
   vector<Player*>* players;
   const string PLAYERS_FILE = "players.csv";
};

// Sort Player vector by high score 
bool sortByHighScore(const Player* lhs, const Player* rhs) {
    return *(lhs) < *(rhs); // operator overload 
}

// Sort Player vector alphabetically
bool sortByUsername(const Player* lhs, const Player* rhs) {
    return (strcmp(lhs->getUsername(), rhs->getUsername()) < 0);
}