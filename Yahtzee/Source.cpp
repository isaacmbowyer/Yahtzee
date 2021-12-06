#include <iostream>
#include <time.h>
#include "PlayerManagement.h";
#include "ScoreCard.h"
using namespace std;


int main() {
#ifdef _DEBUG
    //  _CrtSetBreakAlloc(87);
    _onexit(_CrtDumpMemoryLeaks);
#endif*
 
    PlayerManagement* management = new PlayerManagement();
    management->start();

     // Free Management data 
    management->freeMemory(); 
    management = nullptr; 

    return 0;
}
