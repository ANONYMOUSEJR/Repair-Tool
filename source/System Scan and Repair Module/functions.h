#pragma once

// \003 is a <3.

#include <iostream>

#include <chrono>
#include <thread>

#include "confile.h"

using std::this_thread::sleep_for;
using std::chrono::milliseconds;

#undef max// This somehow fixes an error code that could come from "max()" in the cin.ignore function, 
// Here's where I got it from: [https://stackoverflow.com/a/21959303].

using namespace std;

// Clears out a potentially corrupted cin.
void cinFlush() {
	cin.clear(); // Clears any error flags in the input stream.
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores all characters up until the newline character.
}

void cls() {
	system("cls");
}

void pause() {
	sleep_for(milliseconds(350)); cout << ".";
	sleep_for(milliseconds(350)); cout << ".";
	sleep_for(milliseconds(350)); cout << ".";
	sleep_for(milliseconds(350)); cout << endl;
}

bool isGud(short num) {
	if (cin.fail()) {
		// Input could not be interpreted as a short.
		return false;
	}
	else {
		// Input is a valid short.
		return true;
	}
}

void print(string txt, short spd) {
	short x = 0;
	// Prints out the words letter-by-letter until the end character '\0'. 
	while (txt[x] != '\0') {
		cout << txt[x];
		sleep_for(milliseconds(spd)); // spd default is '1'.
		x++;
	}
}

void border(short spd) {
	print("*****************************************************************\n", spd);
}

void cont(short spd) {
	print("Press ENTER key to continue", spd); pause();
	cinFlush();
	cin.get();
}

void colorChoice(short spd, short &colour, short autoChoice = 0) {
start:
	cls();
	short choice = 0;

	if ((autoChoice > 0) && (autoChoice <= 5)) {
		choice = autoChoice;
		goto skip;
	}

	//cout << "Enter which colour you would like to set the program to:\n";
	print("Enter which colour you would like to have the program use:\n", spd);
	print("1) Light Red.\n", spd);
	print("2) Light Purple.\n", spd);
	print("3) Light Yellow.\n", spd);
	print("4) Light Green.\n", spd);
	print("5) Bright White.\n", spd);
	print("0) Return.\n", spd);
	print("~> ", spd);
	cin >> choice;

	if (!isGud(choice)) {
		goto def;
	}

skip:
	switch (choice) {
	case 1:
		colour = choice;
		system("color c");
		break;

	case 2:
		colour = choice;
		system("color d");
		break;

	case 3:
		colour = choice;
		system("color e");
		break;

	case 4:
		colour = choice;
		system("color a");
		break;

	case 5:
		colour = choice;
		system("color f");
		break;

	case 0:
		return;

	default:
	def:
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		break;
	}
	if (autoChoice > 0) {
		return;
	}
	goto start;
}

void spdChange(short &spd) {
start:
	string choice;
	cls();
	print("Use Print Scrolling?\n", spd);
	if (spd) {
		print("Currently set to: TRUE.", spd);
	}else {
		print("Currently set to: FALSE.", spd);
	}
	print("\nChange? (y/n)\n~> ", spd);
	cin >> choice;

	if (choice[1] != '\0') {
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
	}

	if ((choice[0] == 'y' || choice[0] == 'Y') && spd) {
		spd = 0;
	}
	else if ((choice[0] == 'y' || choice[0] == 'Y') && !spd) {
		spd = 1;
	}
	else if (choice[0] == 'n' || choice[0] == 'N') {
		return;
	}
	goto start;
}

void onProcEnd(short spd, short &power) {
start:
	cls();
	short choice = 0;
	print("The process might take a while to finish\n(it is reccomended to restart after it does).\n", spd);
	print("1) Shutdown, set to: ", spd); if (power == 1) { cout << "TRUE.\n"; } else { cout << "FALSE.\n"; }
	print("2) Restart, set to: ", spd); if (power == 2) { cout << "TRUE.\n"; } else { cout << "FALSE.\n"; }
	print("3) Logout, set to: ", spd); if (power == 3) { cout << "TRUE.\n"; }else { cout << "FALSE.\n"; }
	print("4) Do Nothing, set to: ", spd); if (power == 0) { cout << "TRUE.\n"; } else { cout << "FALSE.\n"; }
	print("0) Return.\n~> ", spd);
	cin >> choice;

	switch (choice){
	case 1:
		power = 1;
		break;

	case 2:
		power = 2;
		break;

	case 3:
		power = 3;
		break;

	case 4:
		power = 0;
		break;

	case 0:
		return;

	default:
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		break;
	}
	goto start;
}

void abort(short power, short spd) {
start:
	cout << endl; border(spd); cout << endl;
	short choice = 0;
	border(spd);
	if (power == 1) {
		print("PC will SHUTDOWN soon", spd); pause();
	}
	else if (power == 2) {
		print("\nPC will RESTART soon", spd); pause();
	}
	else if (power == 3) {
		print("\nPC will LOGOUT soon", spd); pause();
	}
	else if (power == 0) {
		return;
	}

	print("\nWould you like to (1)Abort, (2)Speed things up, or (3)Do nothing?\n~> ", spd);
	cin >> choice;

	if (!isGud(choice)) {
		goto def;
	}

	switch (choice) {
	case 1:
		system("shutdown /a");
		print("ABORTED", spd); pause();
		return;

	case 2:
		if (power == 1) {
			system("shutdown /s /t 0");
		}
		else if (power == 2) {
			system("shutdown /r /t 0");
		}
		else if (power == 3) {
			system("shutdown /l /t 0");
		}
		return;

	case 3:

		print("NOTHING WILL BE DONE", spd); pause();
		return;

	default:
	def:
		cls();
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		break;
	}
	goto start;
}

void end(short power) {
	switch (power){ // 5 mins.
	case 1:
		system("shutdown /s /t 900"); // Shutdown.
		break;

	case 2:
		system("shutdown /r /t 900"); // Restart.
		break;

	case 3:
		system("shutdown /l /t 900"); // Logout.
		break;

	case 0:
		return;
	}
}

void stat(short spd, short power, short colour) {
	cout << setw(28) << "Scrolling effect is set to: ";
	if (spd) {
		print("TRUE.\n", spd);
	}
	else {
		print("FALSE.\n", spd);
	}

	cout << setw(28) << "Power is set to: ";
	if (power == 0) {
		print("DO NOTHING.\n", spd);
	}
	else if (power == 1) {
		print("SHUTDOWN.\n", spd);
	}
	else if (power == 2) {
		print("RESTART.\n", spd);
	}
	else if (power == 3) {
		print("LOGOUT.\n", spd);
	}

	cout << setw(28) << "Colour is set to: ";
	if (colour == 1) {
		print("LIGHT RED.", spd);
	}
	else if (colour == 2) {
		print("LIGHT PURPLE.\n", spd);
	}
	else if (colour == 3) {
		print("LIGHT YELLOW.\n", spd);
	}
	else if (colour == 4) {
		print("LIGHT GREEN.\n", spd);
	}
	else if (colour == 5) {
		print("BRIGHT WHITE.\n", spd);
	}
}

void setMenu(short &spd, short &power, short &colour) {
start:
	cls();
	short choice = 0;
	print("Which setting would you like to access?\n", spd);
	print("1) System Colors.\n", spd);
	print("2) Print Scrolling.\n", spd);
	print("3) Power Settings.\n", spd);
	print("0) return.\n\n\n", spd);
	stat(spd, power, colour);
	if (colour == 1) {
		cout << "\033[4A \r"; cout << "~> "; cin >> choice;
	}
	else {
		cout << "\033[5A \r"; cout << "~> "; cin >> choice;
	}

	if (!isGud(choice)) {
		goto def;
	}

	switch (choice){
	case 1:
		colorChoice(spd, colour);
		break;

	case 2:
		spdChange(spd);
		break;

	case 3:
		onProcEnd(spd, power);
		break;

	case 0:
		saveConf(spd, power, colour);
		return;

	default:
	def:
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		break;
	}
	goto start;
}

void info(short spd) {
start:
	cls();
	short choice = 0;
	print("What do you want to learn about?\n", spd);
	print("1) SFC Scan.\n", spd);
	print("2) DISM CheckHealth.\n", spd);
	print("3) DISM ScanHealth.\n", spd);
	print("4) DISM RestoreHealth.\n", spd);
	print("5) Desktop Unresponsive Fix.\n", spd);
	print("0) Return.\n~> ", spd);
	cin >> choice;
	switch (choice) {
	case 1:
		cls();
		border(spd);
		print("The command used is: \"sfc \\scannow\".\n", spd);
		print("It stands for \"System File Checker\" and when executed,\nit scans all protected system files and replaces corrupted\nor missing files with a cached copy that is located in a\ncompressed folder at %WinDir%\\System32\\dllcache.", spd);
		print("\n\nTLDR; \"sfc /scannow\" is useful for checking and repairing system files,\nwhich can be useful for resolving issues related to system crashes\nor error messages related to missing or corrupted system files.\n", spd);
		print("Will be affected by power settings.\n\n", spd);
		cont(spd);
		break;

	case 2:
		cls();
		border(spd);
		print("The command used is: \"DISM /Online /Cleanup-Image /CheckHealth\"\n", spd);
		print("It stands for \"Deployment Image Servicing and Management\" and is used to repair and prepare Windows images.\nThe \" /Online\" switch specifies that the image to repair is the currently running operating system.\nThe \"/Cleanup-Image\" switch is used to free up space and remove unnecessary files.\nThe \"/CheckHealth\" switch is used to check the health of the operating system image and reports\nwhether it is healthy or if there are any issues that need to be addressed.\nThis command can be used to troubleshoot and repair problems with the operating system,\nand can also be used to prepare an image for deployment.\n", spd);
		print("\n\nTLDR; \"DISM /Online /Cleanup-Image /CheckHealth\" is a good starting point for troubleshooting issues\nwith your operating system, as it quickly checks the health of the image and reports any issues\nthat need to be addressed.\n", spd);
		print("Will NOT be affected by power settings.\n\n", spd);
		cont(spd);
		break;

	case 3:
		cls();
		border(spd);
		print("The command used is: \"DISM /Online /Cleanup-Image /ScanHealth\"\n", spd);
		print("It is similar to the command \"DISM /Online /Cleanup-Image /CheckHealth\" in that it\nuses the Deployment Image Servicing and Management (DISM) tool to repair Windows images.\nHowever, the \"/ScanHealth\" switch scans the operating system for component store corruption,\nand verifies the integrity of all protected system files and replaces corrupted files with a\ncached copy that is located in a compressed folder at %WinDir%\\System32\\dllcache.\nThis command can be used to troubleshoot and repair problems with the operating system.\n", spd);
		print("\n\nTLDR; \"DISM /Online /Cleanup-Image /ScanHealth\" is useful for checking\nthe integrity of the operating system and can be used to fix issues\nrelated to component store corruption.\n", spd);
		print("Will be affected by power settings.\n\n", spd);
		cont(spd);
		break;

	case 4:
		cls();
		border(spd);
		print("The command used is: \"DISM /Online /Cleanup-Image /RestoreHealth\"\n", spd);
		print("It is also uses the Deployment Image Servicing and Management (DISM) tool, and it is used to repair the operating system image.\nThe \"/Online\" switch specifies that the image to repair is the currently running operating system.\nThe \"/Cleanup-Image\" switch is used to free up space and remove unnecessary files.\nThe \"/RestoreHealth\" switch scans the operating system for component store corruption and attempts to repair any issues found using Windows Update.\nThis switch will also check for component corruption, system file corruption, and missing protection registration for the component.\nIf any issues are found, DISM will try to download and replace the corrupted or missing files from Windows Update.\nThis command can be used to troubleshoot and repair problems with the operating system.\n", spd);
		print("\n\nTLDR; \"DISM / Online / Cleanup - Image / RestoreHealth\" is the most comprehensive command,\nas it scans the operating system for component store corruption,\nchecks for component corruption, system file corruption,\nand missing protection registration for the component,\nand then attempts to repair any issues found using Windows Update.\nWill also be amongst the most time consuming options.\n", spd);
		print("Will be affected by power settings.\n\n", spd);
		cont(spd);
		break;

	case 5:
		cls();
		border(spd);
		print("The commands used are: \"taskkill /IM explorer.exe /F\" & \"start explorer.exe\"\n", spd);
		print("\"Taskkill\" terminates programs.\n\"/IM explorer.exe\" specifies that the terminated program is an image by the name of explorer.exe.\n\"/F\" specifies that the process is to be terminated forcefully.\n", spd);
		print("\"start explorer.exe\" just runs the now closed program.\n", spd);
		cont(spd);
		break;

	case 0:
		return;

	default:
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		break;
	}
	goto start;
}

void unresponsiveFix(short spd) {
	string choice;
start:
	cls();
	cinFlush();
	print("The following script will restart explorer.exe, continue? (y/n)\n~> ", spd);
	cin >> choice;

	if (choice[1] != '\0') {
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
	}
	else if (choice[0] == 'y' || choice[0] == 'Y') {
		system("taskkill /IM explorer.exe /F");
		sleep_for(milliseconds(500));
		print("Please select the console again in order to regain the ability to interact with it.\n", spd);
		system("start explorer.exe");
		SetForegroundWindow(GetConsoleWindow()); // Just to hopefully make the window automatically in the foreground.
		cont(spd);
		return;
	}
	else if (choice[0] == 'n' || choice[0] == 'N') {
		return;
	}
	else {
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		goto start;
	}
}

void opMenu(short &spd, short &power, short &colour) {
	print("WARNING: To use the windows functions you Must run this program with elevated privileges,\nEverything else works in normal mode.\nTo full screen press [ALT + ENTER] keys.\n", spd);
	system("timeout /t 3");
start:
	cls();
	short choice = 0;
	print("The following will run the respective Windows functions in an attempt to fix your PC.\n", spd);
	print("1) sfc scan.\n", spd);
	print("2) DISM checkHealth.\n", spd);
	print("3) DISM scanHealth.\n", spd);
	print("4) DISM restoreHealth.\n", spd);
	print("5) All of the above.\n", spd);
	print("6) Desktop Unresponsive Fix.\n", spd);
	print("7) Info.\n", spd);
	print("8) Sytem Info.\n", spd);
	print("9) Settings.\n", spd);
	print("0) Exit.\n~> ", spd);
	cin >> choice;

	if (!isGud(choice)) {
		goto def;
	}

	switch (choice){
	case 1:
		cls();
		system("sfc /scannow");
		end(power);
		system("timeout 15");
		abort(power, spd);
		break;

	case 2:
		cls();
		system("DISM /Online /Cleanup-Image /CheckHealth");
		end(power);
		system("timeout 15");
		abort(power, spd);
		break;

	case 3:
		cls();
		system("DISM /Online /Cleanup-Image /ScanHealth");
		end(power);
		system("timeout 15");
		abort(power, spd);
		break;

	case 4:
		cls();
		system("DISM /Online /Cleanup-Image /RestoreHealth");
		end(power);
		system("timeout 15");
		abort(power, spd);
		break;

	case 5:
		cls();
		system("sfc /scannow");
		system("DISM /Online /Cleanup-Image /CheckHealth");
		system("DISM /Online /Cleanup-Image /ScanHealth");
		system("DISM /Online /Cleanup-Image /RestoreHealth");
		end(power);
		system("timeout 15");
		abort(power, spd);
		break;

	case 6:
		cls();
		unresponsiveFix(spd);
		break;

	case 7:
		cls();
		cinFlush();
		info(spd);
		break;

	case 8:
		cls();
		system("systeminfo && pause");
		break;

	case 9:
		cinFlush();
		setMenu(spd, power, colour);
		break;

	case 0:
		cls();
		print("Thank you for using my program", spd); pause();
		print("\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003\003", spd); //33 Hearts cuz why not?
		return;

	default:
	def:
		cls();
		print("Sorry that input is invalid, try again", spd); cinFlush(); pause();
		break;
	}
	goto start;
}