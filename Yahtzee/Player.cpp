#include "Player.h"

Player::Player(string& username, string& password, int highScore) : highScore(highScore) {
    // Allocate memory for username and password 
    this->username = (char*)malloc(sizeof(char) * (username.length() + 1));
    this->password = (char*)malloc(sizeof(char) * (password.length() + 1));

    // Copy username and password into the required length of the cstring 
    strcpy_s(this->username, username.length() + 1, username.c_str());
    strcpy_s(this->password, password.length() + 1, password.c_str());

}

Player::~Player() {
    free(username);
    free(password);
}


ostream& operator<<(ostream& os, Player& player) {
    // Write player username to file
    os << player.username << ','; 

    // Encypt the password and write it to file
    player.encryptPassword(); 
    os << player.password << ','; 

    // Write the highscore to file 
    os << player.highScore << endl; 

    return os;
}