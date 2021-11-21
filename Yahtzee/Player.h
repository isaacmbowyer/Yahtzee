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

    inline void encryptPassword(); 
    inline void decryptPassword();
    inline void display();

    inline const char* getUsername() const;

    inline const bool operator==(const char* username) const;
    inline const bool operator==(const string& password) const;
    inline const bool operator<(const Player& player) const;

    friend ostream& operator<<(ostream& is, Player& player);

private: 
    char* username;
    char* password;
    int highScore;
};


// Unencrypt the password by subtracting 1 ASCII to each char
void Player::decryptPassword() {
    for (int i = 0; i < strlen(password); i++) {
        password[i]--;
    }
}

// Encrypt the password by adding 1 ASCII to each char
void Player::encryptPassword() {
    for (int i = 0; i < strlen(password); i++) {
        password[i]++;
    }
}

// Displays players username and high score
void Player::display() {
    cout << setw(25) << left << username << highScore << endl;
}

// Return the player username 
const char* Player::getUsername() const {
    return username;
}

// Checks to see if the player username is equal to our inputted username 
const bool Player::operator==(const char* username) const {
    return (strcmp(this->username, username) == 0); //  check if there is a match 
}

// Checks to see if the player username is equal to our inputted password
const bool Player::operator==(const string& password) const {
    return (strcmp(this->password, password.c_str()) == 0); //  check if there is a match  
}

// Checks to see if the player's high score is less than the other players high score 
const bool Player::operator<(const Player& player) const {
    return highScore < player.highScore;
}