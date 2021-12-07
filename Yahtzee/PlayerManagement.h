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
    void freeMemory();
    const string getValidInput(string& field) const; 

    const vector<string> getPlayerData() const;
    void choosePlayer();
    void addPlayer();
    void removePlayer();

    friend bool sortByHighScore(const Player* lhs, const Player* rhs);
    friend bool sortByUsername(const Player* lhs, const Player* rhs);

    friend ostream& operator<<(ostream& os, PlayerManagement& management);
    friend istream& operator>>(istream& is, PlayerManagement& management); 
    friend istream& operator>>(istream& is, int* numberOfPlayers);

private:
   vector<Player*>* players;
   const string PLAYERS_FILE = "players.csv";
   static const int MAX_CHARACTERS;
   static const int MIN_CHARACTERS;
};


// Sort Player vector by high score 
inline bool sortByHighScore(const Player* lhs, const Player* rhs) {
    return *(lhs) < *(rhs); // operator overload 
}

// Sort Player vector alphabetically
inline bool sortByUsername(const Player* lhs, const Player* rhs) {
    return (strcmp(lhs->getUsername(), rhs->getUsername()) < 0);
}

// Free memory
inline void PlayerManagement::freeMemory() {
    delete this; 
}

// Gets the number of players in the csv file 
inline istream& operator>>(istream& is, int* numberOfPlayers) {
    is >> *numberOfPlayers; 
    
    // Go onto the next line
    char newLine;
    is.get(newLine);
    return is;
}

// Write the number of players to the csv file
inline ostream& operator<<(ostream& os, PlayerManagement& management) {
    int numberOfPlayers = management.players->size();  // get number of players

    os << numberOfPlayers << endl; // write the number of players to the file 

    return os;
}