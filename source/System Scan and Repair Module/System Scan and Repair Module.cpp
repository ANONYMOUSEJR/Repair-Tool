#include <iostream>
#include <windows.h>

#include "functions.h"

using namespace std;

int main()
// TODO:
// - Work on the fullscreen functions.
// - Work on the admin checker. (Make the scanners grey if the user does not have admin privaleges and cant use them)
// - Add ding sound for when the scans finish.
// - Make it so that the program checks if changes have been made in the settings before it decides to ask the user if they wanna save.
// - Also, please try and spread the anti empty enter key functionality throughout the solution.
// - Giving the option to the user to check the scan log file: [C:\Windows\Logs\CBS\CBS.log].
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
