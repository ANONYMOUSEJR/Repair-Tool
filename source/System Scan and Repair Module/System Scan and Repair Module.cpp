#include <iostream>
#include <windows.h>

#include "functions.h"

using namespace std;

int main()
/* 
TODO:
- Add a func that asks the user if they want to update config file? (???maybe???)
*/
{
    // To make the program full screen.
    /*
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, WS_POPUP);
    SetForegroundWindow(GetConsoleWindow());
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SetForegroundWindow(GetConsoleWindow());
    */

    short spd = 1, power = 0, color = 4; // Will be replaced by loaded file. Also colour 4 is green.
    loadConf(spd, power, color);
    colorChoice(spd, color, color);
    cls();
    opMenu(spd, power, color);

    return 0;
}
