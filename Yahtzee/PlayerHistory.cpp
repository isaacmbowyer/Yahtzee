#include "PlayerHistory.h"
#include <fstream>

const int PlayerHistory::MAX_HISTORIC_DATA = 3;

// Sets the data 
PlayerHistory::PlayerHistory(string& playerFile) : PLAYER_FILE(playerFile) {
    // Historic data contains Number of Games, Accumulated Score & Average Score 
    historyData = (int*) calloc(PlayerHistory::MAX_HISTORIC_DATA, sizeof(int)); // set all data defaulted to 0 
    getPlayerHistoryData(); // set the array contents for hisory data 

    // ScoreCards is a array of pointers to scorecards which are by themselves a sub-array 
    scoreCards = (int**) malloc(historyData[0] * sizeof(int*));  // retrieve the number of games from the array -> this will be our size 
}

PlayerHistory::~PlayerHistory() {

}
void PlayerHistory::start() {
    int option; 
    do {
        displayPlayerHistory();
        displayMenu(); 

        // Get user option 
        cout << "Please choose an option: "; 
        cin >> option; 
        cin.ignore();
        cin.clear(); 

    } while (option != 9);
}

// Display the Player History Menu
void PlayerHistory::displayMenu() const {
    cout << "1) Play Game" << endl; 
    cout << "2) View Historic scorecards" << endl; 
    cout << "9) Return to player chooser screen" << endl;
    cout << endl;
}

// Display Player's current history 
void PlayerHistory::displayPlayerHistory()  const {
    player->displayAux();  // get the player to display its username and high score
    
    // Print out the rest which is contained in our heap array 
    cout << "Total Games: " << historyData[0] << endl;
    cout << "Accumulated Score: " << historyData[1] << endl;
    cout << "Average Score: " << historyData[2] << endl; 
    cout << endl;
} 

// Get the Number of Games, Accumulated Score & Average Score from the player file 
void PlayerHistory::getPlayerHistoryData() {

    ifstream input(PLAYER_FILE);
    
    // Check if the player has a file
    if (input.is_open()) {
        // Player already has a file, retrieve data from it

        input >> *this;  // Get the first line in the player file 
        
        input.close();  // close file stream 
    }
    // if the player does not have a file (i.e -> new player), do nothing as the historicData array contents is defaulted to 0 (new player = no scores)
}

// Retrieve and set all the player's historic data from the file 
istream& operator>>(istream& is, PlayerHistory& history) {
    char deliminator;
    for (int i = 0; i < PlayerHistory::MAX_HISTORIC_DATA; i++) { // use for loop to reduce repeating code 
        // Read in the first line and add the data to the array 
        is >> history.historyData[i]; 
        is.get(deliminator);
    }
    return is; 
}