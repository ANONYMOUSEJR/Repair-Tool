#include <iostream>
#include <windows.h>

#include "functions.h"

using namespace std;

int main()
// TODO:
// - Add a func that asks the user if they want to update config file? (???maybe???)
// - Make a func specifically for checking the variables instead of making spaggheti code??? (nah...)
//  - Make the function also be able to tell if the given value is a number only... (maybe check if the input between '=' signs is a num)
// - Prettify the config file documentation. (Mostly done)
// 
// ~ I think that i can make like a puzzle game using the file output stuff... that could be a fun project...

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
