// This is a header file that is supposed to create/read a config file.

#pragma once
#undef max

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>

#include "functions.h"

using namespace std;

void _cls() {
	system("cls");
}

void _cinFlush() {
	cin.clear(); // Clears any error flags in the input stream.
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores all characters up until the newline character.
}

void _pause(short x) {
	for (short i = 0; i < x; i++) {
		cout << "Waiting for " << (x - i) << " seconds.";
		Sleep(1000);
		cout << "\r"; // Moves cursor to the beginning of the line, effectiveley clearing it.
	}
}

bool _isGud(short num) {
	if (cin.fail()) {
		// Input could not be interpreted as a short.
		return false;
	}
	else {
		// Input is a valid short.
		return true;
	}
}

void _ask() {
start:
	_cls();
	short choice = 0;
	cout << "Would you like to terminate program to fix issue yourself or would you rather have the program handle it?\n";
	cout << "1) Handle it myself.\n2) Let the program handle it.\n~> ";
	cin >> choice;
	if(!_isGud(choice)) {
		goto bad;
	}
	if (choice == 1) {
		exit(choice); // Failure.
	}
	else if (choice == 2) {
		return;
	}
	else {
	bad:
		cout << "Sorry that input is invalid, try again...\n"; _pause(3); _cinFlush();
	}
	goto start;
}

void saveConf(short spd = 1, short power = 0, short colour = 4) {
	fstream file;
	file.open("config.txt", ios::out);
	if (file.is_open()) {
		file << setw(20) << "Scrolling effect = " << spd << ";" << endl;
		file << setw(20) << "Power settings = " << power << ";" << endl;
		file << setw(20) << "Colour settings = " << colour << ";" << endl;
		// For user info: 
		file << "\n#######################\n";
		file << "\nPutting in wrong values might cause issues in the system, \nplease observe the following info to familiarise yourself with the formatting\n\n";
		file << "1) To allow/disallow the Scrolling effect write a 1/0 next to \"Character scrolling effect\".\n\n";
		file << "2) To change Power setting replace the value with one of the following numbers:\n -" << setw(14) << " Do Nothing = " << "0\n -" << setw(14) << " Shutdown = " << "1\n -" << setw(14) << " Restart = " << "2\n -" << setw(14) << " Logout = " << "3\n\n";
		file << "3) To change Colour settings replace the value with one of the following numbers:\n -" << setw(16) << " Light Red = " << "1\n -" << setw(16) << " Light Purple = " << "2\n -" << setw(16) << " Light Yellow = " << "3\n -" << setw(16) << " Light Green = " << "4\n -" << setw(16) << " Bright White = " << "5\n\n";
		file << "General advice, please do NOT remove the \"#\" or \";\" characters,\nit will cause issues in the program because they are used to tell the scanner what's what.\n\nPlease only enter whole numbers as values to be loaded to avoid issues.\nDon't worry about the distance between the \"=\" sign and the actual variable,\nI just made it like that to make it look pretty lol.\n";
		file.close();
	}
}

void _load(bool x, short spd = 1, short power = 0, short colour = 4) { // If true it will create else it will delete.
	_cls();
	if (x) {
		cout << "Creating file";
	}
	else if (!x) {
		cout << "Deleting file";
	}
	for (short i = 0; i < 3; i++) {
		cout << ".";
		Sleep(500);

		saveConf(spd, power, colour);
	}
	if (x) {
		_cls();
		cout << "File successfully created!\n"; _pause(3);
	}
}

void _remFile() {
	_load(false);
	_cls();
	// Attempt to delete the file
	if (remove("config.txt") != 0) {
		cerr << "Error deleting file!\n"; _pause(3);
	}
	else {
		cout << "File successfully deleted!\n"; _pause(3);
	}
}

void loadConf(short &spd, short &power, short &colour) {
	// Extra simple algorithm to seperate variable values from other characters.
	string x = "", y = "", z = "", line = "";
	short count = 0;
	bool error = false, check = false;
	fstream file;
	file.open("config.txt", ios::in);

	// Filling up the lines.
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
				else { // Simple checking for formatting of values...
					if (c == '=') {
						count++;
						check = true;
					}
					else if (c == ';') {
						check = false;
					}
					else if (c == '#') {
						goto end;
					}
					if (check && c != ' ' && c != '=') {
						error = true;
						cout << "Error: One or more values in the config file are invalid.\n"; _pause(3); goto err;
					}
				}
			}
		}
	end:

		// Check to see if values are valid:
		// spd check:
		if ((stoi(x) != 1) && (stoi(x) != 0)) {
			error = true;
			cout << "Error: One or more values in the config file are invalid.\n"; _pause(3); goto err;
		}

		// power check:
		if ((stoi(y) < 0) || (stoi(y) > 3)) {
			error = true;
			cout << "Error: One or more values in the config file are invalid.\n"; _pause(3); goto err;
		}

		// colour check:
		if ((stoi(z) < 1) || (stoi(z) > 5)) {
			error = true;
			cout << "Error: One or more values in the config file are invalid.\n"; _pause(3); goto err;
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
			_ask();
			_remFile();
		}
		_load(true);
	}
}

bool editConf(short spd = 1) {
	string choice;
	fstream file;
	file.open("config.txt");
	if (file.is_open()) {
		system("notepad.exe config.txt");
		return 0;
	}
	else {
		return 1;
	}
}