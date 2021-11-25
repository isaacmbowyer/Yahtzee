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
    const char* getUsername() const;

    const bool operator==(const char* username) const;
    const bool operator==(const string& password) const;
    const bool operator<(const Player& player) const;

    friend ostream& operator<<(ostream& is, Player& player);

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
    cout << "Highest Score:" << highScore << endl;
}

// Return the player username 
inline const char* Player::getUsername() const {
    return username;
}

// Checks to see if the player username is equal to our inputted username 
inline const bool Player::operator==(const char* username) const {
    return (strcmp(this->username, username) == 0); //  check if there is a match 
}

// Checks to see if the player username is equal to our inputted password
inline const bool Player::operator==(const string& password) const {
    return (strcmp(this->password, password.c_str()) == 0); //  check if there is a match  
}

// Checks to see if the player's high score is less than the other players high score 
inline const bool Player::operator<(const Player& player) const {
    return highScore < player.highScore;
}