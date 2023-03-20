#include <iostream>
#include <windows.h>

#include "functions.h"

using namespace std;

int main()
// TODO:
// - Work on the fullscreen functions.
// 
// ~ I think that I can make like a puzzle game using the file output stuff, that could be a fun project!
{
    // To make the program full screen.
    /*
    SetWindowLong(GetConsoleWindow(), GWL_STYLE, WS_POPUP);
    SetForegroundWindow(GetConsoleWindow());
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SetForegroundWindow(GetConsoleWindow());
    */

    short spd = 1, power = 0, color = 4; // Default values will be replaced by loaded file, if there is one.
    loadConf(spd, power, color);
    colorChoice(spd, color, color);
    cls();
    opMenu(spd, power, color);

    return 0;
}
