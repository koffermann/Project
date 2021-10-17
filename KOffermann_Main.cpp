/*
CS210: Project Two - Airgead Banking App
Name: Kerrian Offermann
Date: October 1, 2021
File: KOffermann_Main.cpp
*/



#include <iostream>
#include <string>
#include "KOffermann_Airgead.h"

using namespace std;

int main() {
	string userEntry = ""; // Initialize user entry string

	BankingApp compoundInterest;

	// Banking App's Main Menu //

	while (true) {
		compoundInterest.SetInterestVariables(); // Call the function created for our main menu

		cout << "Enter C to Continue" << endl;
		cout << "To exit Airgead Banking Mobile App, please enter Q to Quit.";
		cin >> userEntry; // User must enter C to continue or Q to quit -- lower and uppercases allowed

		if (userEntry == "C" || userEntry == "c") { // User can enter lowercase or uppercase 'c'
			compoundInterest.LoadBalances(); // Load balance reports
		}

		else if (userEntry == "Q" || userEntry == "q") {  // User can enter lowercase or uppercase 'q'
			cout << "Thank you for using Airgead Banking. Goodbye." << endl;
			break; // End program if user quits
		}

		else {
			cout << "Invalid input. Please try again." << endl; // Error message if user enters anything but 'c' and 'q'
			break;
		}
	}

	return 0;
}