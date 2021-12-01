#include "PlayerManagement.h"
#include <iomanip>
#include <fstream>
#include <ostream>
#include "PlayerHistory.h"

PlayerManagement::PlayerManagement() {
    // Store player objects as a vector of pointers to vechiles
    players = new vector<Player*>; 
}

PlayerManagement::~PlayerManagement() {

    // Delete each player from the vector
    for (int i = 0; i < players->size(); i++) {
        delete players->at(i);
    }

    // Free player vector 
    delete players;
    players = nullptr;
}

void PlayerManagement::start() {
    cout << "Welcome to Champion Yahtzee" << endl;
    cout << "---------------------------" << endl;

    // Load exisiting players from file 
    getExistingPlayers();

    int chosenOption;  // Store player input 
    do {
        displayExistingPlayers();
        displayMenu();

        // Get Input from user 
        cout << "Please choose an option: ";
        cin >> chosenOption;
        cin.ignore();
        cin.clear();

        // Detect what option the user chose an run it 
        switch (chosenOption) {
        case 1: {
            // choose a player
            choosePlayer(); 
            break;
        }
        case 2:
            // add a player to the vector
            addPlayer();
            break;
        case 3:
            // remove a player from the vector 
            removePlayer();
            break;
        case 4:
            // sort by username
            sort(players->begin(), players->end(), sortByUsername);
            break;
        case 5:
            // sort by high score 
            sort(players->begin(), players->end(), sortByHighScore);
            break;
        }

        cout << endl;
    } while (chosenOption != 9); 

    writeExistingPlayers();
}

// Displays the menu to the user
void PlayerManagement::displayMenu() {
    cout << "1) Choose player" << endl;
    cout << "2) Add player" << endl;
    cout << "3) Remove player" << endl;
    cout << "4) Sort players alphabetically" << endl;
    cout << "5) Sort by highest score" << endl;
    cout << "9) Exit" << endl;
    cout << endl;
}
// Gets the exisiting players inside the csv file 
void PlayerManagement::getExistingPlayers() {
    ifstream input(PLAYERS_FILE);

    if (input.is_open()) {
        // While there are lines in the file
        while (!input.eof()) {
            // Retieving and setting data from file
            input >> *this;
        }

        input.close();  // close file stream 

    }
    else {
        cout << "Cant open file" << endl;
    }
}

void PlayerManagement::writeExistingPlayers() {
    ofstream output(PLAYERS_FILE);
    if (output.is_open()) {
        // Use a for each algorithm to iterate over players vector and use a lambda to write that player details onto the file 
        for_each(players->begin(), players->end(), [&output](Player* player) {
            output << *player; // operator overload to write player to file 
        });
        output.close(); 
    }
    else {
        cout << "Could not open file." << endl; 
    }
}

// Displays all the players inside the vector 
void PlayerManagement::displayExistingPlayers() {
    // Display the Header 
    cout << setw(25) << left << "Player Name" << "Highest Score" << endl;
    cout << setw(25) << left << "-----------" << "-------------" << endl;


    // Use a for_each algorithm to retireve each player object and pass into a lamda expression to call the display method 
    for_each(players->begin(), players->end(), [](Player* currentPlayer) {
        // print details of player
        currentPlayer->display(); 
    });

    cout << endl;
}

// Get the user to input a players username and password 
const vector<string> PlayerManagement::getPlayerData() const {
    string username;
    string password;

    // Get the username 
    cout << "Please enter player username: ";
    getline(cin, username);

    // Get the password
    cout << "Please enter player password: ";
    getline(cin, password);

    // Store player data inside a vector on the heap
    vector<string> playerData;
    playerData.push_back(username);
    playerData.push_back(password);

    return playerData;

}

// Gets the user to pick a player from the vector 
void  PlayerManagement::choosePlayer() {
    // Get the player username and password 
    vector<string> player = getPlayerData();

    int index = -1; // added to 0 at the lambda 
    // Using a find_if algorithm and a lamda expression to find the first match where a player in the vector is equal to our inputted player 
    vector<Player*>::iterator it = find_if(players->begin(), players->end(), [&player, &index](Player* currentPlayer) { // pass in the index so we know where the player is located 
        ++index; // go to the next index 
      
         // Get the username and password from the vector and compare with current player from vector 
        return (*currentPlayer == player.at(0).c_str()) && (*currentPlayer == player.at(1));  // operater overloading 
    });

    if (it != players->end()) {
        // Get player history  
        PlayerHistory* playerHistory = new PlayerHistory(players->at(index));
        playerHistory->start(); 
    }

    else {
        // Error Message, could not found player
        cout << "Invalid username or password" << endl;
    }

}


// Remove a player from the players vector 
void PlayerManagement::removePlayer() {
    // Get the player username and password 
    vector<string> player = getPlayerData();

    // Using a find_if algorithm and a lamda expression to find the first match where a player in the vector is equal to our inputted player to delete 
    vector<Player*>::iterator it = find_if(players->begin(), players->end(), [&player](Player* currentPlayer) { 
        // Get the username and password from the vector and compare with current player from vector 
        return (*currentPlayer == player.at(0).c_str()) && (*currentPlayer == player.at(1));  // operater overloading 
    });

    if (it != players->end()) {
        // Delete the player from the record 
        players->erase(it);
    }
    else {
        // Error message 
        cout << "Invalid username or password" << endl;
    }
}

// Add a new player to the players vector 
void PlayerManagement::addPlayer() {
    // Get the player username and password 
    vector<string> player = getPlayerData();

    // Using a find_if algorithm and a lamda expression to find the first match where if a players whose username is equal to our inputted username, it will be invalid 
    vector<Player*>::iterator it = find_if(players->begin(), players->end(), [&player](Player* currentPlayer) {
        // Get the username and password from the vector and compare with current player from vector 
        return (*currentPlayer == player.at(0).c_str()); // operaotor overloading 
    });

    if (it == players->end()) {
        // Create the player and add to the vector of players 
        players->push_back(new Player(player.at(0), player.at(1)));
    }
    else {
        // Error message 
        cout << "This username already exists" << endl;
    }
}



// Retrieve and set all the playe's history data from the file 
istream& operator>>(istream& is, PlayerManagement& management) {
    string username;
    string password;
    int highScore;
    char endLine;

    // Retrieve and set the data from the record in file
    getline(is, username, ',');
    getline(is, password, ',');
    is >> highScore;
    is.get(endLine);

    // Create the player object 
    Player* newPlayer = new Player(username, password, highScore);

    // Add to the vector of players
    management.players->push_back(newPlayer);

    // Decrypt the password in memory
    newPlayer->decryptPassword();

    return is;
}
