#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Player
{
public:
    Player(string& username, string& password, int highScore = 0);
    ~Player();

    void encryptPassword(); 
    void decryptPassword();
    void display() const;
    void displayAux() const;

    const string convertToLowerCase() const;
    const char* getUsername() const;
    void setHighScore(const int highScore); 

    const bool operator==(const char* username) const;
    const bool operator==(const string& password) const;
    const bool operator>(const int newScore) const;
    const bool operator<(const Player& player) const;
 
    friend ostream& operator<<(ostream& os, Player& player);

private: 
    char* username;
    char* password;
    int highScore;
};


// Unencrypt the password by subtracting 1 ASCII to each char
inline void Player::decryptPassword() {
    for (int i = 0; i < strlen(password); i++) {
        password[i]--;
    }
}

// Encrypt the password by adding 1 ASCII to each char
inline void Player::encryptPassword() {
    for (int i = 0; i < strlen(password); i++) {
        password[i]++;
    }
}

// Displays players username and high score
inline void Player::display() const {
    cout << setw(25) << left << username << highScore << endl;
}

// Displays the username and high score 
inline void Player::displayAux() const {
    cout << "Welcome to Champion Yahtzee " << username << endl;
    cout << "-----------------------------------" << endl;
    cout << "Highest Score:     " << highScore << endl;
}

// Return a lower case version of the players usename 
inline const string Player::convertToLowerCase() const {
    string lowerCaseUsername = "";
    // Lower case the string username 
   
    for (int i = 0; i < strlen(username); i++) {
        char character = tolower(username[i]); 
        lowerCaseUsername = lowerCaseUsername + character;
    }
    return lowerCaseUsername; 
}

// Free username and password
inline Player::~Player() {
    free(username);
    free(password);
}

// Return the player username 
inline const char* Player::getUsername() const {
    return username;
}

// Set the new highScore
inline void Player::setHighScore(const int highScore) {
    this->highScore = highScore; 
}

// Checks to see if the player username is equal to our inputted username 
inline const bool Player::operator==(const char* username) const {
    // convert the username to lowercase 
    return (strcmp(convertToLowerCase().c_str(), username) == 0); //  check if there is a match 
}

// Checks to see if the player username is equal to our inputted password
inline const bool Player::operator==(const string& password) const {
    return (strcmp(this->password, password.c_str()) == 0); //  check if there is a match  
}

// Checks to see if the player's high score is less than the other players high score 
inline const bool Player::operator<(const Player& player) const {
    return highScore < player.highScore;
}

// Checks to see if the new high score is greater than the current highscore  
inline const bool Player::operator>(const int newScore)  const {
    return newScore > highScore; 
}

