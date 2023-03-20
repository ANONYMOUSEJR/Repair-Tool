// This is a function that is supposed to create/read from a config file.

#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "functions.h"

using namespace std;

void _pause(short x) {
	for (short i = 0; i < x; i++) {
		cout << "Waiting for " << (x - i) << " seconds.";
		Sleep(1000);
		cout << "\r"; // Moves cursor to the beginning of the line, effectiveley clearing it.
	}
}

void _remFile() {
// Attempt to delete the file
	if (remove("config.txt") != 0) {
		cerr << "Error deleting file\n"; _pause(3);
	}
	else {
		cout << "File successfully deleted\n"; _pause(3);
	}
}

void saveConf(short spd = 1, short power = 0, short colour = 4) {
	fstream file;
	file.open("config.txt", ios::out);
	if (file.is_open()) {
		file << setw(20) << "Scrolling effect = " << spd << endl;
		file << setw(20) << "Power settings = " << power << endl;
		file << setw(20) << "Colour settings = " << colour << endl;
		// For user info: 
		file << "######################";
		file << "\nPutting in wrong values might cause issues in the system, \nplease observe the following info to familiarise yourself with the formatting\n\n";
		file << "1) To allow/disallow the Scrolling effect write a 1/0 next to \"Character scrolling effect\".\n\n";
		file << "2) To change Power setting replace the value with one of the following numbers:\n - Shutdown = 1\n - Restart = 2\n - Logout = 3\n - Do Nothing = 0\n\n";
		file << "3) To change Colour settings replace the value with one of the following numbers:\n - Light Red = 1\n - Light Purple = 2\n - Light Yellow = 3\n - Light Green = 4\n - Bright White = 5\n\n";
		file << "General advice, please do not remove the \"#\" it will cause issues in the program because it is the divider between the stored variables and documentation.\n\nPlease only enter whole numbers as values to be loaded to avoid issues.\nDon't worry about the distance between the \"=\" sign and the actual variable I just made it like that to make it look pretty lol.\n";
		file.close();
	}
}

void loadConf(short &spd, short &power, short &colour) {
	// Extra simple algorithm to seperate variable values from other characters.
	string x = "", y = "", z = "", line = "";
	short count = 0;
	bool error = false;
	fstream file;
	file.open("config.txt", ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			for (char c : line) {
				if (isdigit(c)) {
					if (count == 1) {
						x += c;
					}
					else if (count == 2) {
						y += c;
					}
					else if (count == 3) {
						z += c;
					}
				} 
				else {
					if (c == '=') {
						count++;
					}
					else if (c == '#') {
						goto end;
					}
				}
			}
		}
	end:

		// Check to see if values are valid:
		// spd check:
		if ((stoi(x) != 1) && (stoi(x) != 0)) {
			error = true;
			cout << "Error: One or more values in the config file are invalid,\ncreating another one with default values\n"; _pause(3); goto err;
		}

		// power check:
		if ((stoi(y) < 0) || (stoi(y) > 3)) {
			error = true;
			cout << "Error: One or more values in the config file are invalid,\ncreating another one with default values\n"; _pause(3); goto err;
		}

		// colour check:
		if ((stoi(z) < 1) || (stoi(z) > 5)) {
			error = true;
			cout << "Error: One or more values in the config file are invalid,\ncreating another one with default values\n"; _pause(3); goto err;
		}
		
		// Simple conversion of the filtered digit strings into integers.
		spd = stoi(x); power = stoi(y); colour = stoi(z);
		file.close();
	}
	else {
		cout << "Error: Config file not found in the current directory,\ncreating a new one with default values.\n"; _pause(3);
	err:
		file.close();
		if (error) {
			_remFile();
		}
		saveConf(spd, power, colour);
	}
}