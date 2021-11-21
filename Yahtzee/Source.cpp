#include <iostream>
#include "PlayerManagement.h";
using namespace std;

int main() {
#ifdef _DEBUG
    //  _CrtSetBreakAlloc(87);
    _onexit(_CrtDumpMemoryLeaks);
#endif
    PlayerManagement* management = new PlayerManagement();
    management->start();

    // Free Management data 
    delete management; 
    management = nullptr;

    return 0;
}