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
    const int findExistingPlayer(vector<string>& player) const ; 
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

// Find an existing player using their username and password 
inline const int PlayerManagement::findExistingPlayer(vector<string>& player) const {
    int index = -1; // added to 0 at the lambda 

   // Using a find_if algorithm and a lamda expression to find the first match where a player in the vector is equal to our inputted player  
    vector<Player*>::iterator it = find_if(players->begin(), players->end(), [&player, &index](Player* currentPlayer) { // pass in the index so we know where the player is located 
        ++index; // go to the next index 

        // Get the lower cased username and password from the vector and compare with current player from vector 
        return (*currentPlayer == player.at(1).c_str()) && (*currentPlayer == player.at(2));  // operater overloading 
    });

    // If the player exists, then send the index, else send -1
    return it != players->end() ? index : -1; 
}

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