#include "PlayerHistory.h"
#include "GameManagement.h"
#include <fstream>
const int PlayerHistory::MAX_HISTORIC_DATA = 3;

// Sets the data 
PlayerHistory::PlayerHistory(Player* player, const string& PLAYER_FILE) : player(player), PLAYER_FILE(PLAYER_FILE) {
    // Game History contains Number of Games, Accumulated Score & Average Score 
    gameHistory = (double*) calloc(PlayerHistory::MAX_HISTORIC_DATA, sizeof(double)); // set all data defaulted to 0 
    getPlayerStats(); // set the array contents for game history

    // Create an array of Scorecard Pointers on the heap by size of Total Games
    scoreCards = new ScoreCard* [gameHistory[0]];
    getScoreCards();
}

PlayerHistory::~PlayerHistory() {
    // Free the scorecards 
    for (int i = 0; i < gameHistory[0]; i++) {
        delete scoreCards[i];
    }
    delete scoreCards; 
    scoreCards = nullptr; 

    // Free the game history 
    delete[] gameHistory; 
    gameHistory = nullptr; 
}

// Starts the Application and runs whichever option the user chose 
void PlayerHistory::start() {
    int chosenOption; 
    do {
        cout << endl; 
        displayPlayerHistory();
        displayMenu(); 

        // Get user option 
        cout << "Please choose an option: "; 
        cin >> chosenOption; 
        cin.ignore();
        cin.clear();
        cout << endl; 
        
        // Detect which option the user choose: 
        if (chosenOption == 1) {
            // Create the game management class
            GameManagement * gameManagment = new GameManagement();
            ScoreCard& card = gameManagment->start();
            
            // Put the new card into the array by reallocating it 
            reallocScoreCards(&card);
         
            // Set the new player history
            int totalScore = card.getTotal();
            setNewGameHistory(totalScore);

            // Set the new Player high score only if it is the highest one 
            if (*player > totalScore) {
                player->setHighScore(totalScore);
            }

            // Delete gameManagament 
            gameManagment->freeMemory();
            gameManagment = nullptr; 

        } 
        
        else if (chosenOption == 2 && gameHistory[0]) {
            // Let the player veiw their scorecards if they have at least 1 game in memory (no total games = no scorecards) 
            gameHistoryMain();
        }

        cout << endl;
    } while (chosenOption != 9);

    // Save all the data to the csv file 
    writePlayerHistory(); 
}

// Allows the User to View their ScoreCards 
void PlayerHistory::gameHistoryMain() {
    int userOption;
    int gamePtr = gameHistory[0];
    ScoreCard* scoreCard;
    do {
        scoreCard = scoreCards[gamePtr - 1]; // We need to base it of the index
        
        // Display the Game Number, ScoreCard and its timestamp 
        scoreCard->displayScoreCard(gamePtr, gameHistory[0]); 

        displayGameHistoryMenu(gamePtr);  

        // Get user option 
        cout << "Please choose an option: ";
        cin >> userOption;
        cin.ignore();
        cin.clear();

        if (userOption == 1 && gamePtr != 1) {
            // Viewing the previous scorecard
            gamePtr--; 
        }

        else if (userOption == 2 && gamePtr != gameHistory[0]) {
            // Viewing the next scorecard
            gamePtr++;
        }

    } while (userOption != 9);

}

// Allows the User to View their ScoreCards 
void PlayerHistory::reallocScoreCards(ScoreCard* newScoreCard) {
    int totalGames = gameHistory[0] + 1; 

    ScoreCard** newScoreCards = new ScoreCard * [totalGames];

    if (gameHistory[0]) {
        // Copy each scorecard into the new array
        for (int i = 0; i < totalGames - 1; i++) {
            ScoreCard* scoreCard = scoreCards[i];
            newScoreCards[i] = scoreCard;
        }
        // Add in the new scorecard
        newScoreCards[totalGames - 1] = newScoreCard;
    } 
    else {
        // This is a new player which now has 1 game -> simply add it in
        newScoreCards[0] = newScoreCard;
    }

    // Delete the previous array and its new contents equal to the new 
    delete[] scoreCards;
    scoreCards = newScoreCards;
   
}

// Display the Player History Menu
void PlayerHistory::displayMenu() const {
    cout << "1) Play Game" << endl; 
    // If there are no games, the player cannot view scorecards as they dont have any 
    if (gameHistory[0]) {
        cout << "2) View historic scorecards" << endl; 
    }
    cout << "9) Return to player chooser screen" << endl; 
}

void PlayerHistory::displayGameHistoryMenu(int gameNumber) const {
    // If we are displaying the 1st game we can not view a previous scorecard as it does not exist 
    if (gameNumber != 1){
        cout << "1) View the previous scorecard" << endl;
    }
    // If we are displaying the last game we can not view the next scorecard as it does not exist 
    if (gameNumber != gameHistory[0]) {
        cout << "2) View the next scorecard" << endl; 
    }
    cout << "9) Return to player statistics screen" << endl; 

}

// Display Player's current history 
void PlayerHistory::displayPlayerHistory()  const {
    player->displayAux();  // get the player to display its username and high score
    
    // Print out the rest which is contained in our heap array 
    cout << "Total Games:       " << gameHistory[0] << endl;
    cout << "Accumulated Score: " << gameHistory[1] << endl;

    cout << "Average Score:     " << gameHistory[2] << endl; 
    cout << endl;
} 


// Get the Number of Games, Accumulated Score & Average Score from the player file 
void PlayerHistory::getPlayerStats() {

    ifstream input(PLAYER_FILE);
    
    // Check if the player has a file
    if (input.is_open()) {
        // Player already has a file, retrieve data from it

        input >> *this;  // Get the first line in the player file 
        
        input.close();  // close file stream 
    }
    // if the player does not have a file (i.e -> new player), do nothing as the gameHistory array contents is defaulted to 0 (new player = no scores)
}

// Get all the scorecards for the chosen player
void PlayerHistory::getScoreCards() {
    ifstream input(PLAYER_FILE);

    string text;
    getline(input, text, '\n'); // ignore the first line as we have already read it 

    if (input.is_open()) {
        for (int i = 0; i < gameHistory[0]; i++) {
            // Create a Scorecard
            ScoreCard* scoreCard = new ScoreCard();

            // Set the data for the scoreCard 
            input >> *scoreCard;

            // Add it to the Array of pointer to Scorecards 
            scoreCards[i] = scoreCard;
        }
    }
}

// Write all the player history to the csv file 
void PlayerHistory::writePlayerHistory() {
    ofstream output(PLAYER_FILE); 
    
    // Write the player history data 
    output << *this;

    // Get each scorecard to write out its own data to the csv file
    for (int i = 0; i < gameHistory[0]; i++) {
        ScoreCard* scorecard = scoreCards[i];
        output << *scorecard;
    }

    output.close(); 
}

// Retrieve and set all the player's game history data from the file (Number of Games, Accumulated and Average Score)
istream& operator>>(istream& is, PlayerHistory& history) {
    char deliminator;
    for (int i = 0; i < PlayerHistory::MAX_HISTORIC_DATA; i++) { // use for loop to reduce repeating code 
        // Read in the first line and add the data to the array 
        is >> history.gameHistory[i]; 
        is.get(deliminator);
    }
    return is; 
}
