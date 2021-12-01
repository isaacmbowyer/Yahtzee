#include <iostream>
#include <stdio.h>      /* puts */
#include <time.h> 
#include "PlayerManagement.h";
using namespace std;

int main() {
#ifdef _DEBUG
    //  _CrtSetBreakAlloc(87);
    _onexit(_CrtDumpMemoryLeaks);
#endif
    // ctime_s(buf, sizeof(buf), &now); 

    
    PlayerManagement* management = new PlayerManagement();
    management->start();

    // Free Management data 
    delete management; 
    management = nullptr;
    
    return 0;
}