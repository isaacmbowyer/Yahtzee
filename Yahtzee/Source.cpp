#include <iostream>
#include <time.h>
#include "PlayerManagement.h";
#include "GameManagement.h"; 
using namespace std;


int main() {
#ifdef _DEBUG
    //  _CrtSetBreakAlloc(87);
    _onexit(_CrtDumpMemoryLeaks);
#endif*
 

  
    GameManagement* gameManagment = new GameManagement(); 
    gameManagment->start(); 


    /*
    PlayerManagement* management = new PlayerManagement();
    management->start();

    // Free Management data 
    delete management; 
    management = nullptr;
    */
    return 0;
}
